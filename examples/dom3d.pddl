(define (domain ewr3)
    (:requirements :typing :negative-preconditions :equality :universal-preconditions :durative-actions :fluents)

    (:types 
     location		   ; either a zone or the "base" location
     zone	- location ; several connected zones, at most 1 robot per zone
     robot		   ; carries at most 1 instrument
     instrument		   ; used by a robot to achieve tasks
     task		   ; activity to be achieved in various zones
     )


  (:constants base - location)

  (:predicates
   (adjacent ?z1  ?z2 - location)    ; location ?z1 is adjacent to ?z2
   (at ?x - robot ?z - location)     ; robot ?x is at location ?z
   (freezone ?z - zone)	     ; there is a robot at zone ?z
   (carry ?r - robot ?i - instrument) ; robot ?r carries an instrument ?i
   (bare ?r - robot)		      ; robot ?r has no instrument
   (achieved ?t - task ?z - zone) ; task ?t in zone ?z has been achieved
   (adapted ?i - instrument ?t - task) ; instrument ?i can be used for task ?t
   (available ?i - instrument)	      ; instrument ?i is available at the base
   (independent ?t -task)
   (require ?t1 ?t2 - task)
   )

  ;; there are 4 operators in this domain:

  ;; move a robot between two adjacent zones, discharge its battery
  (:durative-action Move                                
	   :parameters (?r - robot ?from ?to - zone)
	   :duration  (= ?duration 5)
	   :condition (and (at start (adjacent ?from ?to))
			   (at start (at ?r ?from))
			   (at start (not (= ?from base)))
			   (at start (not (= ?to base)))
			   (over all (freezone ?to))
			   )
	   :effect (and (at end (at ?r ?to))
			(at start (not (at ?r ?from)))
			(at start (freezone ?from))
			(at end (not (freezone ?to)))))

  (:durative-action Bmove                                
	   :parameters (?r - robot ?from -location ?to - zone) 
	   :duration  (= ?duration 5)
	   :condition (and  (at start (adjacent ?from ?to))
			    (at start (at ?r ?from))
			    (at start (= ?from base))
			    (over all (freezone ?to))
			    )
	   :effect (and (at end (at ?r ?to))
			(at start (not (at ?r ?from)))
			(at end (not (freezone ?to)))))
			 
  (:durative-action Moveb                                
	   :parameters (?r - robot ?from - zone ?to -location) 
            :duration  (= ?duration 5)
	   :condition (and (at start (adjacent ?from ?to))
			   (at start (= ?to base))
			   (at start (at ?r ?from))
			   )
	   :effect (and (at end (at ?r ?to))
			(at start (not (at ?r ?from)))
			(at start (freezone ?from))
			))
  

  ;; mount instrument?i on robot at base base
  (:durative-action Mount
	   :parameters (?r - robot ?i - instrument)
	   :duration  (= ?duration 2)
	   :condition (and (over all (at ?r base))
			   (over all (available ?i))
			   (at start (bare ?r)))
	   :effect (and (at end (carry ?r ?i))
			(at end (not (available ?i)))
			(at start (not (bare ?r)))))


  ;; unmount instrument ?i from robot at base base
  (:durative-action Unmount
	   :parameters (?r - robot ?i - instrument)
	   :duration  (= ?duration 2)
	   :condition (and (over all (at ?r base))
			   (at start (carry  ?r ?i)))
	   :effect (and (at start (not (carry ?r ?i)))
	   	   	(at end (available ?i))
			(at end (bare ?r))))


  (:durative-action PerformDep                                
	   :parameters (?t ?t2 - task ?z - zone ?r - robot ?i - instrument)
	   :duration  (= ?duration 10)
	   :condition (and (over all (at ?r ?z))
			   (over all (carry ?r ?i))
			   (at start (adapted ?i ?t))
			   (at start (require ?t ?t2))
			   (at start (achieved ?t2 ?z))
			   )
	   :effect (at end (achieved ?t ?z))
	   )

  (:durative-action PerformIndep                                
	   :parameters (?t - task ?z - zone ?r - robot ?i - instrument)
	   :duration  (= ?duration 10)
	   :condition (and (over all (at ?r ?z))
			   (over all (carry ?r ?i))
			   (at start (adapted ?i ?t))
			   (at start (independent ?t))
			   )
	   :effect (at end (achieved ?t ?z))
	   )
  )



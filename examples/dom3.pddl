(define (domain ewr3)
  
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
   (freezone ?z - location)	     ; there is no robot at zone ?z
   (carry ?r - robot ?i - instrument) ; robot ?r carries an instrument ?i
   (bare ?r - robot)		      ; robot ?r has no instrument
   (achieved ?t - task ?z - zone) ; task ?t in zone ?z has been achieved
   (adapted ?i - instrument ?t - task) ; instrument ?i can be used for task ?t
   (available ?i  - instrument)	      ; instrument ?i is available at the base
   (independent ?t - task)	      ; task ?t can be performed any time
   (require ?t ?tbefore - task) ; ?t requires that ?tbefore to be achieved earlier on same zone
   )


  ;; there are 4 operators in this domain:

  ;; move a robot between two adjacent zones, discharge its battery
 (:action move                                
	   :parameters (?r - robot ?from ?to - location) 
	   :precondition (and (adjacent ?from ?to)
			      (at ?r ?from)
			      (or (= ?to base)
				  (freezone ?to))) 
	   :effect (and (at ?r ?to)
			(not (at ?r ?from))
			(freezone ?from)
			(not (freezone ?to))))
 
  ;; mount instrument?i on robot at base base
  (:action mount
	   :parameters (?r - robot ?i - instrument)
	   :precondition (and (at ?r base)
			      (available ?i)
			      (bare ?r))
	   :effect (and (carry ?r ?i)
			(not (available ?i))
			(not (bare ?r))))

  ;; unmount instrument ?i from robot at base base
  (:action unmount
	   :parameters (?r - robot ?i - instrument)
	   :precondition (and (at ?r base)
			      (carry  ?r ?i))
	   :effect (and (not (carry ?r ?i))
	   	   	(available ?i)
			(bare ?r)))


  ;; perform task ?t at zone ?z by robot ?r with instrument ?i
  (:action perform                               
	   :parameters (?t - task ?z - zone ?r - robot ?i - instrument ?t2 - task)
	   :precondition (and (at ?r ?z)
			      (adapted ?i ?t)
			      (carry ?r ?i)
			      (or (independent ?t)
				  (and (require ?t ?t2) (achieved ?t2 ?z))))
	   :effect (achieved ?t ?z)
	   )
  )



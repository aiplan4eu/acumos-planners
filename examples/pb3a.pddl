(define (problem ewr3a)
  (:domain ewr3)

  (:objects ra rb rc - robot
    	    z1 z2 z3 z4 - zone
	    socle1 brosses1 - instrument
	    buttage binage - task)

  (:init (adjacent z1 z2) (adjacent z2 z1)
	 (adjacent z2 z3) (adjacent z3 z2)
	 (adjacent z3 z4) (adjacent z4 z3)
	 (adjacent z1 base) (adjacent base z1)
	 (adjacent z2 base) (adjacent base z2)
	 (adjacent z4 base) (adjacent base z4)

	 (freezone z1)
	 (freezone z2)
	 (freezone z3)
	 (freezone z4)

	 (at ra base) (bare ra)
	 (at rb base) (bare rb)
	 (at rc base) (bare rc)
	 
	 (available socle1) (available brosses1)
	 
	 (adapted socle1 binage)
	 (adapted brosses1 buttage)

	 (independent binage)
         (require buttage binage)
	 )

  (:goal (and (forall (?z - zone)
		      (and (achieved binage ?z)
			   (achieved buttage ?z)))
	      (at ra base)
	      (at rb base)
	      (at rc base)
	      )
	 )
  )
	 
	 

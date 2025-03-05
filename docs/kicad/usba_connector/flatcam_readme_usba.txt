USBA BOARD

	ISOLATION
	
		Load the F_Mask.gbr
			NON-COPPER REGION
				Boundary Margin: 1.2

		Select the generated noncopper object
			PAINT AREA
				Tool Diam: 0.2
				Overlap: 0.4
				Margin: 0
				[X] Standard

		Select the genrated noncopper_iso
			CREATE CNC Job
				Cut Z: -0.25
				Travel Z: 3
				Feed Rate: 120
				Tool Dia: 0.1

	DRILL

		like normal


	EDGE CUT

		isolation
			tool diam: 0.9
			passes: 2
			overlap: 0.3

		edit, break, and delete inner edges

		cnc job
			Cut Z: -2
			Feed Rate: 60
			multi_depth [x]
			depth/pass: 0.25



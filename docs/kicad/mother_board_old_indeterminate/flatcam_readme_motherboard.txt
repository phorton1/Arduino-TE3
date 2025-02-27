mother_board

	changing standard isolate depth to 0.16 feed rate 60
	changing standard cutout and big hole depth to -1.80
	leave drilled & milled small holes at -2.00

	COPY CROSS HAIR (x10y5) gcode from another plot (or create)

	ISOLATE.gcode

		pass1: (develop single line outlines at max distance)
			tool diam:		0.20
			# passes:		1
			pass_overlap:	0.75

			select the iso
			edit geometry
			break edge outline & delete
			delete outline around ground island at right in small pins
			delete edge & all outer isolate outlines (leave holes)
			update geometry
			unplot it

		pass2: (clean up fills)
			tool diam:		0.5
			width:			4
			pass overlap:	0.75

			select the iso
			edit geometry
			break edge outlines
			delete edge outlines and holes
			update geometry

		combine geometry
			select two (ctrl-select)
			and use "join geometry" command
			edit geometry and add any needed fills
			upddate geometry

		Generate CNC job on Combo geometry
			Cut Z: -0.16
			Feed Rate: 60

			Note: I accidentally made it 80mm/min so used 70% feed scaling while machining
			Note: I actually made the cutz -0.2, and still had to add live-z -1.2 while
			      machining to get it to cut everywhere

	DRILLS

		sort_drills mother_board.drl 148
		select 0.8 and generate iso
		select 0.9 and 1.0 and generate iso

		create 03-DRILL_08.gcode
		create 04-DRILL_09.gcode

	MILL SLOTS

		SVG's were produced mirrored cuz of 148 param to sort_drills
		open 0.9
		cut Z: -1.75
		multi-depth: [x]
		dapth/pass: 0.25

	MILL HOLES

		go back to the drl file and select the 3.2
		MILL HOLES tool tia: 1.9 generate geometry
		use -1.8 depth and multi-pass

	CUTOUT

		because of sideways "U" shape, has to be drawn manually
		open the edge_cut gerber
		isolate 1.9, single pass, to get lines
		edit geometry
		draw new lines
		delete old ones
		update geometry
		generate cnc - gcode

	LASER

		open and mirror back_mask gerber
		Non-copper region boundry margin 2.0

		geometry object Paint Area
	
		tool diam 0.4
		overlap 0.0
		margin 0.2
		seed based

		generate cnc job (0.1mm tool)

			cutz: 20
			travelz: 20
			feed: 300
			tool diam: 0.1
			spindle speed: 40

		generate gcode
		edit gcode and change m03 to m04


BOARD

	starts at abs 50,33 (3 up in standard 150x100 box)
	cross hair is at 10,5 within that


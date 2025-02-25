ROW BOARD (NEW)

	Cross Hair:  8,6
		edited to CutZ -0.15
			and Feed Rate: 60

	ISOLATION:
	
		Using 20 degree bit, assuming 0.3mm cut width
			used dremel with new bit to try to create
			0.25-0.3mm slightly bevelled tip.
		WENT BACK TO BROKEN BIT after dremel bit failed first few cuts
			re-probed at -1,0, and it was too deep, so I set LiveZ to 0.04
			for effective depth of -0.11
		TURNED RPMS up to near max to try to save bit from breaking

		With ground plane set to 0.11 margin and all
			traces with 0.3mm separation

		tool: 0.25
		passes: 7
		overlap: 0.6

		break and remove all edge outlines
		draw corner marks for placing tape

		CNC Job

			Cut Z: -0.15
			Feed Rate: 60
			Tool Diam: 0.01

		Stats:
			started at:		1:00
			finished at:	2:45 (approx)
			duration:		1:45

	DRILLS

		Depth 2.0

		0.8 normal
		1.0 => 0.9 normal
		1.8 => mill with 0.9mm end mill
		3.2 => mill with 1.9mm end mill

	EDGE CUTS

		depth -1.75
		rate: 100
		usual 1.9 isolation with delete of inner rect

	LASER

		Spindle at absolute -11.2 after homing
		with yellow tape 3mm above spindle mount
		for good (big) dot

		non-copper region boundry 3
		Paint:
			tool diam: 0.4
			overlap: 0
			margin: 0.2
		CNC
			cut: 20
			travel: 20
			feed: 400
			tool dia: 0.1
			spindle: 60

		Stats:
			started at 4:10
			finish: 4:45
			duration: 35

		had to re-align laser after first few movements
		lots of goobers - DONT WIPE WITH PAPER TOWEL!!
		toothbrush, vacuum, sand, vacuum, toothbrush, vacuum

		400x60 is too hot unless the dot is big.
		I ended up using spindle 80% and liveZ to change the dot
			effectively spindle 48
			
		It is damn hard to get the epoxy right
		looking into an airbrush to do it


---------------------- OLD -----------------------------

ROW BOARD

	pcb is at 20,20 abs
	zero is at 24,24 abs
	cross hair is at 8,6 relative
    isolate cut depth: -0.2
	drill and cutout depth: -2
	
	pass1:
		tool: 0.125
		# passes: 1
		overlap: 0
	pass2:
		tool: 0.3
		# passes: 7
		overlap: 0.5

	laser

		geometry object Paint Area

		tool diam 0.4
		overlap 0.0
		margin 0.2
		seed based

		CNC
			feed: 400
			spindle: 60

PANELIZATION

	Create the Panelized PCB file

		Open the good main PCB file.

		Turn off the visibility of the Dwgs.User, Ec01.User
			and Ec02.User layers

		Saving the row_board.kicad_pcb file to row_board_xN.kicad_pcb
			where N is an integer from 2 to 5.

		Select the entire board, and right click to "Create Array" command.
			Horizontal Count:	1
			Vertical Count:		N
			Horizontal Spacing: 0
			Veritcal Spacing:	-28

		Hide the Rats Nest for sanity

		Plot the F.Cu, F.Mask,	Edge.Cuts, and Drill file to
			a plot_xN subdirectory.
		
		Open a DosBox, cd to the plot_xN directory and run
			sort_drills	row_board_xN.drl

		Run FlatCam and start a new project with the F.Cu gerber file

	ISOLATION (better settings for single board as well)

		The trick is to shrink the ground plane offsets to
			0.11 margin  and 0.10 min.  This allows two cuts
			around all pads, without that annoying big space
			that causes copper artifacts, effetively limiting
			the "fill cuts" to inside areas (and not surrounding
			pads with 8 lines)

		tool: 0.14
		passes: 8
		overlap: 0.3

		break and remove all edge outlines

	DRILLS

		0.8 normal
		1.0 => 0.9 normal
		1.8 => mill with 0.9mm end mill
		3.2 => mill with 1.9mm end mill

	EDGE CUTS
		Normal (isolate 1.9, edit & delete inner)

	LASER

		(1) Non-copper region
			boundry margin: 2

		(2) noncopper Paint Area

			tool diam 0.4
			overlap 0.0
			margin 0.2
			seed based

		CNC
			cut: 20
			travel: 20
			tool dia: 0.1
			feed: 400
			spindle: 60

		Spindle at absolute -11.2 after homing
		with yellow tape 3mm above spindle mount
		for good (big) dot

		


Notes on isolation bits

	The bigger boards are much flatter

	1Oz copper is 0.034mm +/- 0.07mm

	The width of my cuts depends on
		- the actual penetration depth
		- the angle of the bit (20 or 45 degrees)
		- the width and condition of the tip of the bit

	Excarbating factors include:
		- the rails are not solid and probably bend in the midle
		- the bed itself appears to be out of tram (0.0 is lower left)

				0.0				0.42
				0.30			0.64

		- the bit will cut in one direction, but not the other
		  - back to front will tend to "dig" in, wherea
		    front to back will tend to "drag" on the surface.
		  - left-to-right or right-to-left depend on the entry
		    and direction changes
		- can't separate the horizontal and vertial feed rates
		  in flatcam on entry into copper (slower entry might work
		  better, but the whole project can't be slowed down)

	I set the default penetration to 0.20mm ... IF THIS WERE THE CASE,
	measured at the top of the 0.035mm thickness of the copper

		with 20 degree bit, the surface separation would be 2*0.035, or 0.07mm
		with 45 degree bit, the surface separation would be 2*0.082, or 0.164mm
		THIS AMOUNT IS ADDED TO THE WIDTH OF THE TIP ITSELF

		Brand new 20's dont have a discernable tip width
		I have 3 used ones, in order:
			- 0.2mm
			- 0.4mm
			- 0.5mm
		New ones typically break in the first few seconds of use
		
		All my open 45's are bent or broken
		- 0.01
		- 0.25
		- 0.3mm
		- 0.4


EXPERIMENTS

	Doing an experiment with global feed rate at 60,
	using G01 Z-0.2000 F20 for z axis moves, with a
	live Z of +0.05 to bring it to Z-0.15

	- Broke the tip doing the cross hairs at F80
	  so, what was 0.2 is now 0.4-ish with an angle,
	  and I now need to re-mesh

	- will try again, with live Feed rate = 0.2 for the
	  cross hairs,  will start isolate with live F=0.5
	  so that Z moves will be F05 and movement will initially be 30
	  VERY SLOW TEST

	- I saw a guy online that uses 0.05mm depth in two passes

	I'm gonna try 0.1mm depth (by adjusting liveZ to +0.1)

	Also will run at max rpm for the start of the test ...
	
	- after the crosshairs and the first pad, I bumped the
	  live Z to 1.4, so we're only going down to -0.06. It's
	  cutting with ridulously slow Z feed rate of 0.5*20 = 10mm
	  per minute (from Z3, that's 20 seconds for every entry)
	  and movement feed rate of 0.5*60=30mm per minute.

	  the cuts still look like 0.3-0.5mm ...

	  PAINFULLY SLOW

	  So, I changed to F100% =>ZF=20, MF=60, and took it up
	  another 0.02mm, so now depth is only 0.04mm.

	  The motor is hot already, so I need to turn it down too,
	  from 11K to around 8.5K









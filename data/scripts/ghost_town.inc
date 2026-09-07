EventScript_GhostTown_ShuppetInteract::
	lock
	faceplayer
	random 8
	switch VAR_RESULT
	case 0, EventScript_GhostTown_ShuppetMsg0
	case 1, EventScript_GhostTown_ShuppetMsg1
	case 2, EventScript_GhostTown_ShuppetMsg2
	case 3, EventScript_GhostTown_ShuppetMsg3
	case 4, EventScript_GhostTown_ShuppetMsg4
	case 5, EventScript_GhostTown_ShuppetMsg5
	case 6, EventScript_GhostTown_ShuppetMsg6
	case 7, EventScript_GhostTown_ShuppetMsg7
	end

EventScript_GhostTown_ShuppetMsg0::
	msgbox gText_GhostTown_Shuppet0
	release
	end

EventScript_GhostTown_ShuppetMsg1::
	msgbox gText_GhostTown_Shuppet1
	release
	end

EventScript_GhostTown_ShuppetMsg2::
	msgbox gText_GhostTown_Shuppet2
	release
	end

EventScript_GhostTown_ShuppetMsg3::
	msgbox gText_GhostTown_Shuppet3
	release
	end

EventScript_GhostTown_ShuppetMsg4::
	msgbox gText_GhostTown_Shuppet4
	release
	end

EventScript_GhostTown_ShuppetMsg5::
	msgbox gText_GhostTown_Shuppet5
	release
	end

EventScript_GhostTown_ShuppetMsg6::
	msgbox gText_GhostTown_Shuppet6
	release
	end

EventScript_GhostTown_ShuppetMsg7::
	msgbox gText_GhostTown_Shuppet7
	release
	end

EventScript_GymShuppetInteract::
	lock
	faceplayer
	msgbox gText_GymShuppet
	release
	end

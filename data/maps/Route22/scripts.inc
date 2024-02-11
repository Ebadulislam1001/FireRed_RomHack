.set LOCALID_RIVAL, 1

Route22_MapScripts::
	.byte 0

Route22_EventScript_EarlyRivalTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	setobjectxyperm LOCALID_RIVAL, 25, 5
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_RIVAL, 25, 6
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRivalTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_RIVAL, 25, 7
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRival::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_ENCOUNTER_RIVAL, 0
	addobject LOCALID_RIVAL
	call Route22_EventScript_RivalApproach
	delay 6
	msgbox Route22_Text_EarlyRivalIntro
	setvar VAR_LAST_TALKED, LOCALID_RIVAL
	call Route22_EventScript_EarlyRivalSquirtle
	msgbox Route22_Text_EarlyRivalPostBattle
	closemessage
	delay 10
	playbgm MUS_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, Route22_EventScript_RivalExit
	call_if_eq VAR_TEMP_1, 1, Route22_EventScript_RivalExit
	call_if_eq VAR_TEMP_1, 2, Route22_EventScript_RivalExitBottom
	fadedefaultbgm
	removeobject LOCALID_RIVAL
	setvar VAR_MAP_SCENE_ROUTE22, 2
	releaseall
	end

Route22_EventScript_RivalApproach::
	applymovement LOCALID_RIVAL, Route22_Movement_RivalApproach
	waitmovement 0
	return

Route22_EventScript_EarlyRivalSquirtle::
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_RivalExit::
	applymovement LOCALID_RIVAL, Route22_Movement_RivalExit
	waitmovement 0
	return

Route22_EventScript_RivalExitBottom::
	applymovement LOCALID_RIVAL, Route22_Movement_RivalExitBottom
	waitmovement 0
	return

Route22_Movement_RivalApproach::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route22_Movement_RivalExit::
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route22_Movement_RivalExitBottom::
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route22_EventScript_LateRivalTriggerTop::
	lockall
	setvar VAR_TEMP_1, 0
	setobjectxyperm LOCALID_RIVAL, 25, 5
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRivalTriggerMid::
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm LOCALID_RIVAL, 25, 6
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRivalTriggerBottom::
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm LOCALID_RIVAL, 25, 7
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRival::
	textcolor NPC_TEXT_COLOR_MALE
	playbgm MUS_ENCOUNTER_RIVAL, 0
	addobject LOCALID_RIVAL
	call Route22_EventScript_RivalApproach
	delay 6
	msgbox Route22_Text_LateRivalIntro
	setvar VAR_LAST_TALKED, LOCALID_RIVAL
	call Route22_EventScript_LateRivalSquirtle
	msgbox Route22_Text_LateRivalPostBattle
	closemessage
	delay 10
	playbgm MUS_RIVAL_EXIT, 0
	call_if_eq VAR_TEMP_1, 0, Route22_EventScript_RivalExit
	call_if_eq VAR_TEMP_1, 1, Route22_EventScript_RivalExit
	call_if_eq VAR_TEMP_1, 2, Route22_EventScript_RivalExitBottom
	fadedefaultbgm
	removeobject LOCALID_RIVAL
	setvar VAR_MAP_SCENE_ROUTE22, 4
	releaseall
	end

Route22_EventScript_LateRivalSquirtle::
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE, Route22_Text_LateRivalDefeat
	return

Route22_EventScript_LeagueGateSign::
	msgbox Route22_Text_LeagueGateSign, MSGBOX_SIGN
	end

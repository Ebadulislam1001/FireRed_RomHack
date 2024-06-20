.equ LOCALID_AIDE,         6

PewterCity_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PewterCity_OnTransition
	.byte 0

PewterCity_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_PEWTER_CITY
	setvar VAR_MAP_SCENE_PEWTER_CITY_MUSEUM_1F, 0
	end

PewterCity_EventScript_RunningShoesAideTrigger0::
	lockall
	setobjectxyperm LOCALID_AIDE, 36, 20
	delay 30
	call PewterCity_EventScript_AideGiveRunningShoes
	releaseall
	end
PewterCity_EventScript_RunningShoesAideTrigger1::
	lockall
	setobjectxyperm LOCALID_AIDE, 36, 21
	delay 30
	call PewterCity_EventScript_AideGiveRunningShoes
	releaseall
	end
PewterCity_EventScript_RunningShoesAideTrigger2::
	lockall
	setobjectxyperm LOCALID_AIDE, 36, 22
	delay 30
	call PewterCity_EventScript_AideGiveRunningShoes
	releaseall
	end
PewterCity_EventScript_RunningShoesAideTrigger3::
	lockall
	setobjectxyperm LOCALID_AIDE, 36, 23
	delay 30
	call PewterCity_EventScript_AideGiveRunningShoes
	releaseall
	end

PewterCity_EventScript_AideGiveRunningShoes::
	msgbox PewterCity_Text_OhPlayer
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PewterCity_Movement_PlayerNoticeAide
	waitmovement 0
	applymovement LOCALID_AIDE, PewterCity_Movement_AideApproachPlayer
	waitmovement 0
	delay 30 
	textcolor NPC_TEXT_COLOR_MALE
	applymovement LOCALID_AIDE, Common_Movement_Delay48
	waitmovement 0
	msgbox PewterCity_Text_AskedToDeliverThis
	textcolor NPC_TEXT_COLOR_NEUTRAL
	playfanfare MUS_OBTAIN_KEY_ITEM
	message PewterCity_Text_ReceivedRunningShoesFromAide
	waitmessage
	waitfanfare
	msgbox PewterCity_Text_SwitchedShoesWithRunningShoes
	special DisableMsgBoxWalkaway
	signmsg
	msgbox PewterCity_Text_ExplainRunningShoes
	normalmsg
	call EventScript_RestorePrevTextColor
	msgbox PewterCity_Text_MustBeGoingBackToLab
	closemessage
	applymovement LOCALID_AIDE, PewterCity_Movement_AideExit
	waitmovement 0
	delay 30
	textcolor NPC_TEXT_COLOR_NEUTRAL
	msgbox PewterCity_Text_RunningShoesLetterFromMom
	closemessage
	removeobject LOCALID_AIDE
	setflag FLAG_SYS_B_DASH
	setvar VAR_MAP_SCENE_PEWTER_CITY, 2
	return

PewterCity_Movement_PlayerNoticeAide::
	walk_left
	step_end

PewterCity_Movement_AideApproachPlayer::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

PewterCity_Movement_AideExit::
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

PewterCity_EventScript_GymGuideTrigger::
	lockall
	message PewterCity_Text_DontLeaveTheTownYet
	waitmessage
	delay 85
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	msgbox PewterCity_Text_YouNeedGymBadges
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, PewterCity_Movement_PreventPlayerFromLeaving
	waitmovement 0
	delay 30
	msgbox PewterCity_Text_GoTakeOnBrock
	closemessage
	releaseall
	end

PewterCity_Movement_PreventPlayerFromLeaving::
	walk_left
	walk_left
	step_end

PewterCity_EventScript_MuseumGuide::
	lock
	faceplayer
	msgbox PewterCity_Text_DidYouCheckOutMuseum, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_EventScript_CheckedOutMuseum
	msgbox PewterCity_Text_ReallyYouHaveToGo
	closemessage
	release
	end

PewterCity_EventScript_CheckedOutMuseum::
	msgbox PewterCity_Text_WerentThoseFossilsAmazing
	release
	end

PewterCity_EventScript_BugCatcher::
	lock
	faceplayer
	msgbox PewterCity_Text_DoYouKnowWhatImDoing, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, PewterCity_EventScript_KnowWhatTheyreDoing
	msgbox PewterCity_Text_SprayingRepelToKeepWildMonsOut
	release
	end

PewterCity_EventScript_KnowWhatTheyreDoing::
	msgbox PewterCity_Text_ThatsRightItsHardWork
	release
	end

PewterCity_EventScript_Lass::
	lock
	faceplayer
	msgbox PewterCity_Text_ClefairyCameFromMoon, MSGBOX_NPC
	release
	end

PewterCity_EventScript_FatMan::
	lock
	faceplayer
	famechecker FAMECHECKER_BROCK, 2
	msgbox PewterCity_Text_BrockOnlySeriousTrainerHere
	release
	end

PewterCity_EventScript_TrainerTips::
	msgbox PewterCity_Text_TrainerTipsEarningEXP, MSGBOX_SIGN
	end

PewterCity_EventScript_PoliceNotice::
	msgbox PewterCity_Text_CallPoliceIfInfoOnThieves, MSGBOX_SIGN
	end

PewterCity_EventScript_MuseumSign::
	msgbox PewterCity_Text_MuseumOfScience, MSGBOX_SIGN
	end

PewterCity_EventScript_GymSign::
	lockall
	famechecker FAMECHECKER_BROCK, 0
	msgbox PewterCity_Text_GymSign
	releaseall
	end

PewterCity_EventScript_CitySign::
	msgbox PewterCity_Text_CitySign, MSGBOX_SIGN
	end

@ 842

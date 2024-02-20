SeafoamIslands_B2F_MapScripts::
	.byte 0

SeafoamIslands_B2F_EventScript_Regice::
	lock
	goto_if_unset FLAG_UNLOCK_POSTGAME_LEGENDARIES, SeafoamIslands_B2F_EventScript_NormalRock
	goto_if_set FLAG_FOUGHT_REGICE, SeafoamIslands_B2F_EventScript_NormalRock
	message SeafoamIslands_B2F_Text_NotANormalRock
	waitmessage
	playmoncry SPECIES_REGICE, CRY_MODE_ENCOUNTER
	waitmoncry
	delay 20
	playbgm MUS_ENCOUNTER_GYM_LEADER, 0
	waitbuttonpress
	setwildbattle SPECIES_REGICE, 5
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, SeafoamIslands_B2F_EventScript_DefeatedRegice
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, SeafoamIslands_B2F_EventScript_RanFromRegice
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SeafoamIslands_B2F_EventScript_RanFromRegice
	setflag FLAG_FOUGHT_REGICE
	release
	end

SeafoamIslands_B2F_EventScript_NormalRock::
	lock
	msgbox SeafoamIslands_B2F_Text_JustANormalRock
	closemessage
	release
	end

SeafoamIslands_B2F_EventScript_DefeatedRegice::
	setflag FLAG_FOUGHT_REGICE
	goto EventScript_RemoveStaticMonRegi
	end

SeafoamIslands_B2F_EventScript_RanFromRegice::
	setvar VAR_0x8004, SPECIES_REGICE
	goto EventScript_MonFlewAwayRegi
	end

SeafoamIslands_B2F_Text_JustANormalRock::
    .string "It's just a normal rock!\p"
    .string "...\p"
    .string "Or is it ?$"

SeafoamIslands_B2F_Text_NotANormalRock::
    .string "This Rock is making some sounds\p"
    .string "...\p"
    .string "Aaaahhh!!!$"


SecretCave_MapScripts::
	.byte 0

SecretCave_EventScript_SuperNerd::
	lock
	faceplayer
	msgbox Secretcave_Text_GuessANumber
	waitmessage
	setvar VAR_TEMP_1, 0
	call SecretCave_EventScript_0th_Place
	call SecretCave_EventScript_1st_Place
	call SecretCave_EventScript_2nd_Place
	call SecretCave_EventScript_3rd_Place
	call SecretCave_EventScript_4th_Place
	call SecretCave_EventScript_5th_Place
	call SecretCave_EventScript_6th_Place
	call SecretCave_EventScript_7th_Place
	call SecretCave_EventScript_8th_Place
	call SecretCave_EventScript_9th_Place
	buffernumberstring STR_VAR_1, VAR_TEMP_1
	msgbox Secretcave_Text_YourOriginalNumber
	waitmessage
	release
	end

SecretCave_EventScript_0th_Place::
	msgbox Secretcave_Text_IsOriginalNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_1
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_1::
	addvar VAR_TEMP_1, 1
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return

SecretCave_EventScript_1st_Place::
	msgbox Secretcave_Text_IsThisNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_2
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_2::
	addvar VAR_TEMP_1, 2
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return

SecretCave_EventScript_2nd_Place::
	msgbox Secretcave_Text_IsThisNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_4
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_4::
	addvar VAR_TEMP_1, 4
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return

SecretCave_EventScript_3rd_Place::
	msgbox Secretcave_Text_IsThisNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_8
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_8::
	addvar VAR_TEMP_1, 8
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return

SecretCave_EventScript_4th_Place::
	msgbox Secretcave_Text_IsThisNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_16
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_16::
	addvar VAR_TEMP_1, 16
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return

SecretCave_EventScript_5th_Place::
	msgbox Secretcave_Text_IsThisNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_32
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_32::
	addvar VAR_TEMP_1, 32
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return

SecretCave_EventScript_6th_Place::
	msgbox Secretcave_Text_IsThisNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_64
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_64::
	addvar VAR_TEMP_1, 64
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return

SecretCave_EventScript_7th_Place::
	msgbox Secretcave_Text_IsThisNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_128
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_128::
	addvar VAR_TEMP_1, 128
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return

SecretCave_EventScript_8th_Place::
	msgbox Secretcave_Text_IsThisNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_256
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_256::
	addvar VAR_TEMP_1, 256
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return

SecretCave_EventScript_9th_Place::
	msgbox Secretcave_Text_IsThisNumberOdd, MSGBOX_YESNO
	call_if_eq VAR_RESULT, YES, SecretCave_EventScript_Add_512
	msgbox Secretcave_Text_NowHalfThisNumber
	waitmessage
	closemessage
	return

SecretCave_EventScript_Add_512::
	addvar VAR_TEMP_1, 512
	msgbox Secretcave_Text_DecreaseThisNumberBy1
	waitmessage
	closemessage
	return


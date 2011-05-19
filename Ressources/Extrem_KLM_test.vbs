dim objShell, iMax, iMin, iRndNumber, check
const Rounds = 1000

set objShell = WScript.CreateObject("WScript.Shell")
objShell.Run("main") 


iMax = 15
iMin = 1
check = 1

WScript.Sleep 1000
objShell.SendKeys "1{ENTER}"
WScript.Sleep 4000


For i = 1 To Rounds

	WScript.Sleep 100
	Randomize
	iRndNumber = Int(((200 - iMin + 1) * Rnd) + iMin)

	objShell.sendkeys iRndNumber & "{TAB}"

	WScript.Sleep 100
	Randomize
	iRndNumber = Round((iMax - iMin + 1) * Rnd + iMin, 2)
	objShell.sendkeys iRndNumber & "{TAB}" 

	Randomize
	if (rnd < 0.1) AND (check = 0) then
		WScript.Sleep 100
		objShell.sendkeys "{ESC}" & "{TAB}"
		check = 1
	Else 
		check = 0
	End If 
Next 


check = 1
objShell.SendKeys "{ESC}{TAB}{ESC}{TAB}"
WScript.Sleep 2000
objShell.SendKeys "2{ENTER}"
WScript.Sleep 4000


For i = 1 To Rounds

	WScript.Sleep 100
	Randomize
	iRndNumber = Int(((200 - iMin + 1) * Rnd) + iMin)

	objShell.sendkeys iRndNumber & "{TAB}"

	WScript.Sleep 100
	Randomize
	iRndNumber = Round((iMax - iMin + 1) * Rnd + iMin, 2)
	objShell.sendkeys iRndNumber & "{TAB}" 

	Randomize
	if (rnd < 0.1) AND (check = 0) then
		WScript.Sleep 100
		objShell.sendkeys "{ESC}" & "{TAB}"
		check = 1
	Else 
		check = 0
	End If 
Next 


check = 1
objShell.SendKeys "{ESC}{TAB}{ESC}{TAB}"
WScript.Sleep 2000
objShell.SendKeys "3{ENTER}"
WScript.Sleep 4000


For i = 1 To Rounds

	WScript.Sleep 100
	Randomize
	iRndNumber = Int(((200 - iMin + 1) * Rnd) + iMin)

	objShell.sendkeys iRndNumber & "{TAB}"

	WScript.Sleep 100
	Randomize
	iRndNumber = Round((iMax - iMin + 1) * Rnd + iMin, 2)
	objShell.sendkeys iRndNumber & "{TAB}" 

	Randomize
	if (rnd < 0.1) AND (check = 0) then
		WScript.Sleep 100
		objShell.sendkeys "{ESC}" & "{TAB}"
		check = 1
	Else 
		check = 0
	End If 
Next 


check = 1
objShell.SendKeys "{ESC}{TAB}{ESC}{TAB}"
WScript.Sleep 2000
objShell.SendKeys "4{ENTER}"
WScript.Sleep 4000


For i = 1 To Rounds

	WScript.Sleep 100
	Randomize
	iRndNumber = Int(((200 - iMin + 1) * Rnd) + iMin)

	objShell.sendkeys iRndNumber & "{TAB}"

	WScript.Sleep 100
	Randomize
	iRndNumber = Round((iMax - iMin + 1) * Rnd + iMin, 2)
	objShell.sendkeys iRndNumber & "{TAB}" 

	Randomize
	if (rnd < 0.1) AND (check = 0) then
		WScript.Sleep 100
		objShell.sendkeys "{ESC}" & "{TAB}"
		check = 1
	Else 
		check = 0
	End If 
Next 


objShell.SendKeys "{ESC}{TAB}{ESC}{TAB}"


WScript.echo "Fertig!"
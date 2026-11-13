;-------------------------
;-| RUGAL by JtheSaltyy |-
;-------------------------
;      - COMMANDS -
;-------------------------

;================================================


;=[ CONTROL SCHEME ]=

[Remap]
x = x
y = y
z = z
a = a
b = b
c = c
s = s


;=[ DEFAULT VALUES ]=

[Defaults]
command.time = 16
command.buffer.time = 1


;=[ SUPER COMMANDS ]=

[Command]
name = "MAX Genocide Destruction"
command = ~D, DF, F, D, DF, F, x+y
time = 32

[Command]
name = "Genocide Destruction"
command = ~D, DF, F, D, DF, F, x
time = 32

[Command]
name = "Genocide Destruction"
command = ~D, DF, F, D, DF, F, y
time = 32

[Command]
name = "MAX Dead End Screamer"
command = ~D, DB, B, D, DB, B, a+b
time = 32

[Command]
name = "Dead End Screamer"
command = ~D, DB, B, D, DB, B, a
time = 32

[Command]
name = "Dead End Screamer"
command = ~D, DB, B, D, DB, B, b
time = 32

[Command]
name = "MAX Genocide Haven"
command = ~D, DF, F, D, DF, F, a+b
time = 32

[Command]
name = "Genocide Haven"
command = ~D, DF, F, D, DF, F, a
time = 32

[Command]
name = "Genocide Haven"
command = ~D, DF, F, D, DF, F, b
time = 32

[Command]
name = "MAX Gigantic Pressure"
command = ~D, DF, F, $D, B, x+y
time = 32

[Command]
name = "Gigantic Pressure"
command = ~D, DF, F, $D, B, x
time = 32

[Command]
name = "Gigantic Pressure"
command = ~D, DF, F, $D, B, y
time = 32


;=[ SPECIAL COMMANDS ]=

[Command]
name = "Enhanced Genocide Cutter"
command = ~F, D, DF, a+b

[Command]
name = "Genocide Cutter"
command = ~F, D, DF, a

[Command]
name = "Genocide Cutter"
command = ~F, D, DF, b

[Command]
name = "Enhanced Kaiser Wave"
command = ~F, B, $D, F, x+y
time = 32

[Command]
name = "Kaiser Wave"
command = ~F, B, $D, F, x
time = 32

[Command]
name = "Kaiser Wave"
command = ~F, B, $D, F, y
time = 32

[Command]
name = "Enhanced Dark Smash"
command = ~B, $D, F, x+y
time =  24

[Command]
name = "Dark Smash"
command = ~B, $D, F, x
time =  24

[Command]
name = "Dark Smash"
command = ~B, $D, F, y
time =  24

[Command]
name = "Enhanced Reppuken"
command = ~D, DF, F, x+y

[Command]
name = "Reppuken"
command = ~D, DF, F, x

[Command]
name = "Reppuken"
command = ~D, DF, F, y

[Command]
name = "Enhanced Dark Barrier"
command = ~B, $D, F, a+b
time = 24

[Command]
name = "Dark Barrier"
command = ~B, $D, F, a
time = 24

[Command]
name = "Dark Barrier"
command = ~B, $D, F, b
time = 24

[Command]
name = "Enhanced Genocide Raid"
command = ~F, $D, B, a+b
time = 24

[Command]
name = "Genocide Raid"
command = ~F, $D, B, a
time = 24

[Command]
name = "Genocide Raid"
command = ~F, $D, B, b
time = 24

[Command]
name = "Enhanced God Press"
command = ~F, $D, B, x+y
time = 24

[Command]
name = "God Press"
command = ~F, $D, B, x
time = 24

[Command]
name = "God Press"
command = ~F, $D, B, y
time = 24

[Command]
name = "Super Jump"
command = ~$D, $U
time = 8


;=[ DOUBLE TAP ]=

[Command]
name = "FF"
command = F, F
time = 10

[Command]
name = "BB"
command = B, B
time = 10


;=[ 2 ATTACK BUTTONS ]=

[Command]
name = "recovery"
command = x+y
time = 1

[Command]
name = "ab"
command = x+y
time = 1

[Command]
name = "cd"
command = a+b
time = 1

;=[ SINGLE BUTTON ]=

[Command]
name = "a"
command = x
time = 1

[Command]
name = "b"
command = y
time = 1

[Command]
name = "c"
command = a
time = 1

[Command]
name = "d"
command = b
time = 1

[Command]
name = "abc"
command = c
time = 1

[Command]
name = "start"
command = s
time = 1

[Command]
name = "up"
command = U
time = 1

[Command]
name = "down"
command = D
time = 1

[Command]
name = "fwd"
command = F
time = 1

[Command]
name = "back"
command = B
time = 1


;=[ HOLD BUTTON ]=

[Command]
name = "holda"
command = /x
time = 1

[Command]
name = "holdb"
command = /y
time = 1

[Command]
name = "holdc"
command = /a
time = 1

[Command]
name = "holdd"
command = /b
time = 1

[Command]
name = "holdabc"
command = /c
time = 1

[Command]
name = "holdp"
command = /x
time = 1

[Command]
name = "holdp"
command = /y
time = 1

[Command]
name = "holdk"
command = /a
time = 1

[Command]
name = "holdk"
command = /b
time = 1

[Command]
name = "holdfwd"
command = /$F
time = 1

[Command]
name = "holdback"
command = /$B
time = 1

[Command]
name = "holdup"
command = /$U
time = 1

[Command]
name = "holddown"
command = /$D
time = 1


;==================================
;==========[ COMMANDS ]============
;==================================


[Statedef -1]


;===[ AI MOTIONS ]===


;=[ AI SYSTEM MOVES ]=

[State -1 Dodge]
type = changestate
value = cond(var(59), 710, 700)
triggerall = AIlevel && numenemy
triggerall = statetype = S && roundstate = 2 && ctrl 
triggerall = Enemy, NumProj != 0 || Enemy, HitDefAttr = SCA, AP || Enemy, NumHelper > 0
triggerall = p2bodydist x >= 150
triggerall = inguarddist
Trigger1 = Random < AILevel * cond(var(59), 8, 125)

[State -1, Guard]
type = changestate
value = 120
trigger1 = AIlevel && numenemy
trigger1 = roundstate = 2 && inguarddist
trigger1 = ctrl && (stateno != [120, 155])
trigger1 = !(enemynear, hitdefattr = SCA, AT) && (enemynear, time < 120)
trigger1 = cond(statetype != A, 1, p2statetype = A)
trigger1 = random < 125 * AILevel

;=[ AI NORMALS ]=

[State -1, Light Kick]
type = ChangeState
value = 230
triggerAll = AILevel && NumEnemy
triggerAll = RoundState = 2 && StateType != A
triggerAll = (P2BodyDist x = [0,60]) && (P2Dist y = 0) && P2StateType != L
triggerAll = (EnemyNear, const(size.head.pos.y) <= -40) || (EnemyNear, StateType = A)
trigger1 = (ctrl || (StateNo = [100,101])) && Random < AILevel * 100

[State -1, Crouching Light Kick]
type = ChangeState
value = 430
triggerAll = AILevel && NumEnemy
triggerAll = RoundState = 2 && StateType != A
triggerAll = (P2BodyDist x = [0, 20]) && (P2Dist y = [-64, 0]) && P2StateType != L
triggerAll = EnemyNear, StateType != A
trigger1 = (ctrl || (StateNo = [100,101])) && Random < AILevel * 120

[State -1, Taunt]
type = changestate
value = 195
triggerall = AIlevel && numenemy
triggerall = statetype != A && life >= 0.5 * lifemax
triggerall = (enemynear, life) <= 0.5 * (enemynear, lifemax)
trigger1 = ctrl
trigger1 = p2dist x >= 160 && !(enemynear, ctrl)
trigger1 = (enemynear, movetype = H) && (enemynear, hitfall) && random < AILevel * 100

;=[ AI SPECIALS ]=

[State -1, Genocide Cutter]
type = ChangeState
value = 1200
triggerAll = AILevel && NumEnemy
triggerAll = RoundState = 2 && StateType != A
triggerAll = (P2BodyDist x = [-32,32]) && (P2Dist y = [-85,0]) && P2StateType != L
triggerAll = (EnemyNear, const(size.head.pos.y) <= -40) || (EnemyNear, StateType = A)
trigger1 = (ctrl || (StateNo = [100,101])) && Random < AILevel * 64

[State -1, Dark Barrier]
type = changestate
value = 1300
triggerall = AIlevel && numenemy
triggerall = roundstate = 2 && statetype != A
triggerall = enemy, ctrl = 0
triggerall = Enemy, NumProj != 0 || Enemy, HitDefAttr = SCA, AP || Enemy, NumHelper > 0
triggerall = p2bodydist x >= 150
triggerall = inguarddist
trigger1 = ctrl && random < AILevel * 125

[State -1, Dark Smash]
type = changestate
value = 1600
triggerall = AIlevel && numenemy
triggerall = roundstate = 2 && statetype = A
triggerall = !movecontact
triggerall = p2bodydist x >= 80 && p2dist y >= 80
trigger1 = ctrl && random < AILevel * 125

;=[ AI AIR ]=

[State -1, Jump-In Attack]
type = changestate
value = 640
triggerall = AILevel && NumEnemy
triggerall = RoundState = 2
triggerall = P2StateType = A && P2StateType != L
triggerall = (stateno = 50 || stateno = 51) && Vel Y >= 0
trigger1 = P2BodyDist X < 64
trigger1 = StateNo != [600, 699]
trigger1 = StateType = A
trigger1 = Ctrl
trigger1 = Random < AILevel * 125

[State -1, Air Hard]
type = changestate
value = 640
trigger1 = AILevel && NumEnemy
trigger1 = RoundState = 2
trigger1 = P2BodyDist X < 75
trigger1 = (StateNo != 210 || PrevStateNo != 610) || (StateNo != 640 || PrevStateNo != 640)
trigger1 = StateType = A
trigger1 = (StateNo = 610 && MoveContact = 1) || (StateNo = 640 && MoveContact = 1)
trigger1 = Random < AILevel * 125

;=[ AI SAFE-PLAY ]=

[State -1 Throw]
type = changestate
value = 900
triggerall = stateno != 52
triggerall = AIlevel && numenemy
triggerall = StateType != A && p2statetype != A
triggerall = roundstate = 2 && ctrl 
trigger1 = Enemy, StateType != L && P2BodyDist X <= 32 && (P2BodyDist Y = [-64, 64])
Trigger1 = Random < AILevel * 125

[State -1, Run/Dash]
type = changestate
value = cond(var(59), 100, 102)
trigger1 = AIlevel && numenemy
trigger1 = roundstate = 2 && statetype != A && ctrl
trigger1 = P2BodyDist X >= 128
trigger1 = EnemyNear, MoveType != A
Trigger1 = Random < AILevel * 125

[State -1, Jump]
type = changestate
value = 40
trigger1 = AIlevel && numenemy
trigger1 = roundstate = 2 && statetype != A && ctrl
trigger1 = P2BodyDist X = [35, 100]
trigger1 = EnemyNear,StateType != A && EnemyNear,StateType= L
Trigger1 = Random < AILevel * 125 

[State -1, Jump]
type = changestate
value = 40
trigger1 = AILevel && NumEnemy
trigger1 = StateType != A && Roundstate = 2
trigger1 = ctrl
trigger1 = numtarget
trigger1 = target,Pos Y = [-150,-100]
trigger1 = target,backedgebodydist <= 0
trigger1 = frontedgedist < 50

[State -1, Guard Counter]
type = ChangeState
value = 780
trigger1 = stateno = 150 || stateno = 151
trigger1 = AILevel && NumEnemy
trigger1 = power >= 500 && !Var(59)
trigger1 = StateType != A
Trigger1 = Random < AILevel * 8
trigger1 = P2BodyDist X = [-32, 64]

[State -1, Power Charge]
type = changestate
value = 750
triggerall = !var(59)
triggerall = AIlevel && numenemy
triggerall = roundstate = 2 && statetype != A && ctrl
triggerall = power < const(data.power) && power < powermax
triggerall = !inguarddist && p2dist x >= 160
Triggerall = Random < AILevel * 125
trigger1 = stateno != 750

;=[ AI RECOVERY ]=

[State -1, Fall Recovery]
type = changestate
value = 5210
trigger1 = AIlevel && numenemy
trigger1 = roundstate = 2 && alive
trigger1 = stateno = 5050 && canrecover
trigger1 = vel y > 0 && pos y < -20
Trigger1 = Random < AILevel * 125

[State -1, Fall Recovery]
type = changestate
value = 5200
trigger1 = AIlevel && numenemy
trigger1 = roundstate = 2 && alive
trigger1 = stateno = 5050 && gethitvar(fall.recover)
trigger1 = vel y > 0 && pos y >= -20
Trigger1 = Random < AILevel * 125


;=====[ PLAYER COMMANDS ]=====


;===[ SUPERS ]===



;=[ GIGANTIC PRESSURE ]=

[State -1, Gigantic Pressure]
type = ChangeState
value = cond(Var(58) | life <= 200 || command = "MAX Gigantic Pressure" && !Var(59) && Power >= 3000, 3210, 3200)
triggerall = !AILevel
triggerall = command = "Gigantic Pressure" || command = "MAX Gigantic Pressure" && !Var(59) && Power >= 3000
triggerall = power >= cond(var(59), 3000, 1000)
triggerall = statetype != A
trigger1 = ctrl
trigger2 = Var(1) || (StateNo = [1000, 2999]) && fvar(6) && Var(59)
trigger3 = Var(59) && StateNo = 1500 && AnimElemTime(17) > 0


;=[ DEAD END SCREAMER ]=

[State -1, Dead End Screamer]
type = ChangeState
value = cond(Var(58) | life <= 200 || command = "MAX Dead End Screamer" && !Var(59) && Power >= 3000, 3110, 3100)
triggerall = !AILevel
triggerall = command = "Dead End Screamer" || command = "MAX Dead End Screamer" && !Var(59) && Power >= 3000
triggerall = power >= cond(var(59), 3000, 1000)
triggerall = statetype != A
trigger1 = ctrl
trigger2 = Var(1) || (StateNo = [1000, 2999]) && fvar(6) && Var(59)
trigger3 = Var(59) && StateNo = 1500 && AnimElemTime(17) > 0


;=[ GENOCIDE DESTRUCTION ]=

[State -1, Genocide Destruction]
type = ChangeState
value = cond(Var(58) | life <= 200 || command = "MAX Genocide Destruction" && !Var(59) && Power >= 3000, 3310, 3300)
triggerall = !AILevel
triggerall = command = "Genocide Destruction" || command = "MAX Genocide Destruction" && !Var(59) && Power >= 3000
triggerall = power >= cond(var(59), 3000, 1000)
triggerall = statetype != A
trigger1 = ctrl
trigger2 = Var(1) || (StateNo = [1000, 2999]) && fvar(6) && Var(59)
trigger3 = Var(59) && StateNo = 1500 && AnimElemTime(17) > 0


;=[ GENOCIDE HAVEN ]=

[State -1, Genocide Haven]
type = ChangeState
value = cond(Var(58) | life <= 200 || command = "MAX Genocide Haven" && !Var(59) && Power >= 3000, 3010, 3000)
triggerall = !AILevel
triggerall = command = "Genocide Haven" || command = "MAX Genocide Haven" && !Var(59) && Power >= 3000
triggerall = power >= cond(var(59), 3000, 1000)
triggerall = statetype != A
trigger1 = ctrl
trigger2 = Var(1) || (StateNo = [1000, 2999]) && fvar(6) && Var(59)



;===[ COMBO CONDITION ]===

[State -1, Combo condition Reset]
type = VarSet
trigger1 = 1
var(1) = 0

[State -1, Combo condition Check]
type = VarSet
trigger1 = statetype != A
trigger1 = ctrl
trigger2 = (stateno = [200, 499])
trigger2 = stateno != 350
trigger2 = movecontact
var(1) = 1



;===[ SPECIALS ]===



;=[ KAISER WAVE ]=

[State -1, Kaiser Wave]
type = ChangeState
triggerall = !AILevel
value = cond(command = "Enhanced Kaiser Wave" && Power >= 500 && !Var(59), 1130, 1100)
triggerall = command = "Kaiser Wave" || command = "Enhanced Kaiser Wave" && Power >= 500 && !Var(59)
trigger1 = var(1)


;=[ REPPUKEN ]=

[State -1, Reppuken]
type = ChangeState
triggerall = !AILevel
value = cond(command = "Enhanced Reppuken" && Power >= 500 && !Var(59), 1030, 1000)
triggerall = command = "Reppuken" || command = "Enhanced Reppuken" && Power >= 500 && !Var(59)
triggerall = !numhelper(1005)
trigger1 = var(1)
trigger2 = Var(59) && StateNo = 1500 && AnimElemTime(17) > 0


;=[ GOD PRESS ]=

[State -1, God Press]
type = ChangeState
triggerall = !AILevel
value = cond(command = "Enhanced God Press" && Power >= 500 && !Var(59), 1430, 1400)
triggerall = command = "God Press" || command = "Enhanced God Press" && Power >= 500 && !Var(59)
trigger1 = var(1)
trigger2 = Var(59) && StateNo = 1500 && AnimElemTime(17) > 0


;=[ DARK BARRIER ]=

[State -1, Dark Barrier]
type = ChangeState
triggerall = !AILevel
value = cond(command = "Enhanced Dark Barrier" && Power >= 500 && !Var(59), 1330, 1300)
triggerall = command = "Dark Barrier" || command = "Enhanced Dark Barrier" && Power >= 500 && !Var(59)
trigger1 = var(1)
trigger2 = Var(59) && StateNo = 1500 && AnimElemTime(17) > 0


;=[ DARK SMASH ]=

[State -1, Dark Smash]
type = ChangeState
triggerall = !AILevel
value = cond(command = "Enhanced Dark Smash" && Power >= 500 && !Var(59), 1630, 1600)
triggerall = command = "Dark Smash" || command = "Enhanced Dark Smash" && Power >= 500 && !Var(59)
trigger1 = statetype = A && Ctrl || (StateNo = [600, 640]) && MoveContact


;=[ GENOCIDE CUTTER ]=

[State -1, Genocide Cutter]
type = ChangeState
triggerall = !AILevel
value = cond(command = "Enhanced Genocide Cutter" && Power >= 500 && !Var(59), 1230, 1200)
triggerall = command = "Genocide Cutter" || command = "Enhanced Genocide Cutter" && Power >= 500 && !Var(59)
trigger1 = var(1)
trigger2 = Var(59) && StateNo = 1500 && AnimElemTime(17) > 0


;=[ GENOCIDE RAID ]=

[State -1, Genocide Raid]
type = ChangeState
triggerall = !AILevel
value = cond(command = "Enhanced Genocide Raid" && Power >= 500 && !Var(59), 1530, 1500)
triggerall = command = "Genocide Raid" || command = "Enhanced Genocide Raid" && Power >= 500 && !Var(59)
trigger1 = var(1)




;=====[ SYSTEM MOVES ]=====

[State -1, Throw]
type = ChangeState
value = 900
triggerall = !AILevel
trigger1 = ctrl
trigger1 = command = "ab" || command = "cd"
trigger1 = statetype != A

[State -1, Super Jump]
type = ChangeState
value = 41
triggerall = !AILevel && roundstate = 2 && statetype != A && !Var(59)
trigger1 = ctrl && command = "Super Jump" 

[State -1, Power Charge]
type = ChangeState
value = 750
triggerall = !AILevel
trigger1 = ctrl && !var(59) && power < powermax
trigger1 = command = "holdabc"
trigger1 = statetype != A

[State -1, EX Mode]
type = ChangeState
value = 760
triggerall = !AILevel
trigger1 = power >= 3000
trigger1 = ctrl && var(59) && !var(58)
trigger1 = command = "abc"
trigger1 = statetype != A

[State -1, Guard Counter]
type = ChangeState
value = 780
triggerall = !AILevel
trigger1 = power >= cond(var(59), 1500, 500)
trigger1 = stateno = 150 || stateno = 152
trigger1 = command = "c" && command = "d"
trigger1 = statetype != A

[State -1, Roll]
type = ChangeState
value = 700
triggerall = !AILevel
trigger1 = command = "a" && command = "c"
trigger1 = (command = "holdfwd" || command = "holdback") && !Var(59)
trigger1 = statetype != A
trigger1 = ctrl

[State -1, Dodge]
type = ChangeState
value = 710
triggerall = !AILevel
trigger1 = command = "a" && command = "c"
trigger1 = Var(59)
trigger1 = statetype != A
trigger1 = ctrl

[State -1, Run/Dash]
type = ChangeState
triggerall = !AILevel
value = cond(!var(59), 102, 100)
trigger1 = command = "FF"
trigger1 = statetype = S
trigger1 = ctrl

[State -1, Run Back]
type = ChangeState
value = 105
triggerall = !AILevel
trigger1 = command = "BB"
trigger1 = statetype = S
trigger1 = ctrl


;=====[ NORMALS ]=====


;=[ CRUSHING BLOW ]=

[State -1, Crushing Blow]
type = ChangeState
value = 350
triggerall = !AILevel
triggerall = !Var(59)
triggerall = command = "b" && command = "d"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl

;=[ FORWARD + WEAK KICK ]=

[State -1, Command Normal]
type = ChangeState
value = 300
triggerall = !AILevel
triggerall = command = "c" && command = "holdfwd"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl
trigger2 = (stateno = 230 || stateno = 210 || stateno = 240) && movecontact > 0

;=[ WEAK PUNCH ]=

[State -1, Stand Light Punch]
type = ChangeState
value = 200
triggerall = !AILevel
triggerall = command = "a"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl

;=[ STRONG PUNCH ]=

[State -1, Stand Strong Punch]
type = ChangeState
value = 210
triggerall = !AILevel
triggerall = command = "b"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl

;=[ WEAK KICK ]=

[State -1, Stand Light Kick]
type = ChangeState
value = 230
triggerall = !AILevel
triggerall = command = "c"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl
trigger2 = stateno = 430 && movecontact > 0

;=[ STRONG KICK ]=

[State -1, Standing Strong Kick]
type = ChangeState
value = 240
triggerall = !AILevel
triggerall = command = "d"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl

;=[ TAUNT ]=

[State -1, Taunt]
type = ChangeState
value = 195
triggerall = !AILevel
triggerall = command = "start"
trigger1 = statetype != A
trigger1 = ctrl

;=[ CROUCHING WEAK PUNCH ]=

[State -1, Crouching Weak Punch]
type = ChangeState
value = 400
triggerall = !AILevel
triggerall = command = "a"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl

;=[ CROUCHING STRONG PUNCH ]=

[State -1, Crouching Strong Punch]
type = ChangeState
value = 410
triggerall = !AILevel
triggerall = command = "b"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl

;=[ CROUCHING WEAK KICK ]=

[State -1, Crouching Weak Kick]
type = ChangeState
value = 430
triggerall = !AILevel
triggerall = command = "c"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl

;=[ CROUCHING STRONG PUNCH ]=

[State -1, Crouching Strong Kick]
type = ChangeState
value = 440
triggerall = !AILevel
triggerall = command = "d"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl

;=[ AIR WEAK PUNCH ]=

[State -1, Jump Light Punch]
type = ChangeState
value = 600
triggerall = !AILevel
triggerall = command = "a"
trigger1 = statetype = A
trigger1 = ctrl

;=[ AIR STRONG PUNCH ]=

[State -1, Jump Strong Punch]
type = ChangeState
value = 610
triggerall = !AILevel
triggerall = command = "b"
trigger1 = statetype = A
trigger1 = ctrl

;=[ AIR WEAK KICK ]=

[State -1, Jump Light Kick]
type = ChangeState
value = 630
triggerall = !AILevel
triggerall = command = "c"
trigger1 = statetype = A
trigger1 = ctrl

;=[ AIR STRONG KICK ]=

[State -1, Jump Strong Kick]
type = ChangeState
value = 640
triggerall = !AILevel
triggerall = command = "d"
trigger1 = statetype = A
trigger1 = ctrl
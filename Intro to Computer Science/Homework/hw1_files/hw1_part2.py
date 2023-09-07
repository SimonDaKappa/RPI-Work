def speedcalc(minutes,seconds,miles,target):
    sect = (60*minutes + seconds)
    pace = sect /miles
    pacemins =  pace / 60
    pacesec = (pace % 60)
    speed = miles / ((minutes/60)+(seconds/3600))
    t1 = pace * target
    targetmin = t1 / 60
    targetsec = t1 % 60
    print("\nPace is ",int(pacemins), "minutes and",int(pacesec),"seconds per mile.")
    print('Speed is',"{:.2f}".format(speed),"miles per hour.")
    print("Time to run the target distance of","{:.2f}".format(target),"miles is",int(targetmin),"minutes and",int(targetsec),"seconds.")

minute = input('Minutes ==> ')
print(minute)
minute = int(minute)
sec = input('Seconds ==> ')
print(sec)
sec = int(sec)
mile = input("Miles ==> ")
print(mile)
mile = float(mile)
tmile = input('Target Miles ==> ')
print(tmile)
tmile = float(tmile)
speedcalc(minute,sec,mile,tmile)


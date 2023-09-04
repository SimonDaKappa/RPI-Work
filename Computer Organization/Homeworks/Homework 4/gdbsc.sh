file ./bomb
break level_one
run
stepi
stepi
stepi
stepi
stepi
set *(int*)($rbp - 4) = 1
stepi
stepi
stepi
stepi
stepi
stepi
stepi

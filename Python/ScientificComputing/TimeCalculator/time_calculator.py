def add_time(start, duration):

    ending = bool()
    horasFinal = 0
    minutosFInal=0
    extraHoras = 0

    #separamos el PM y el AM de la hora
    n = start.split()
    
    #separamos las horas y minutos de mi start
    horasStart, minutosStart = n[0].split(":")
    
    
    #separamos los minutos y horas que le vamos a sumar
    horasDuaration, minutosDuration = duration.split(":")
    
    #me fijo si esta en PM o AM, AM = True, PM = False
    if (n == "AM"):
        ending = True
    else:
        ending = False
        
        
    minutosFInal = int(minutosStart)
    for _ in range(int(minutosDuration)):
        if (minutosFInal==60):
            minutosFInal=0
            extraHoras+=1
        minutosFInal+=1      
    
    horasFinal = int(horasStart)
    for _ in range(int(horasDuaration)+int(extraHoras)):
        if (horasFinal==12):
            horasFinal = 0
            ending = not ending
        horasFinal+=1
    
    if (ending == True):
        ending = "AM"
    else:
        ending = "PM"
    
    tiempoFInal = "{0:02d}:{1:02d} {2}".format(horasFinal,minutosFInal,ending)
    
    return tiempoFInal
    
   
    
        




    return 0
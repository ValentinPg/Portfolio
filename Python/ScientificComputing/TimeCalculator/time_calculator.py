def add_time(start, duration):

    ending = bool() # aca va almacenado el PM y el AM
    #horas minutos y minutos que luego voy a imprimir
    horasFinal = 0
    minutosFInal=0
    
    #variable que almacena el "exceso" de horas al sumar minutos
    extraHoras = 0
    
    #variable que almacena el "exceso" de horas dias al sumar horas
    extraDias = 0

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
        
    #calulo los minuts con un ciclo que va sumando de a 1, asi puedo verificar si llegué a 60
    minutosFInal = int(minutosStart)
    for _ in range(int(minutosDuration)):
        minutosFInal+=1 
        if (minutosFInal==60):
            minutosFInal=0
            extraHoras+=1 #agrego un excedente de minutos a horas
             
    
    #calulo las horas con un ciclo que va sumando de a 1, asi puedo verificar si llegué a 12
    horasFinal = int(horasStart)
    for _ in range(int(horasDuaration)+int(extraHoras)):
        horasFinal+=1
        if ((horasFinal == 12) and (not ending)):
            extraDias+=1
        if (horasFinal==13):
            horasFinal = 1
            ending = not ending #cambio de AM a PM y viceversa
        
        
        
    
    #paso el ending a AM y PM para imprimirlo
    if (ending == True):
        ending = "AM"
    else:
        ending = "PM"
        
    #calculate days later
    daysLater = str()
    if (extraDias==1):
        daysLater = "(next day)"
    elif (extraDias>1):
        daysLater = f"{extraDias} days later"
    
    tiempoFInal = "{0:02d}:{1:02d} {2} ({3})".format(horasFinal,minutosFInal,ending,daysLater)
    
    return tiempoFInal
    
   
    
        




    return 0
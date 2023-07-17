# FALTA ARREGLA EL TEMA DEL PARAMETRO OPCIONAL

def add_time(start, duration, day=None):

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
    if (n[1] == "AM"):
        ending = True
    elif (n[1] == "PM"):
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
        
        #si esta en 12 lo reseteo a 0
        if (horasFinal == 12):
            horasFinal = 0
        
        horasFinal+=1
        #me fijo si son las 12 para cambiar de AM a PM y además si hubo un cambio de dia
        if ((horasFinal==12)):
            ending = not ending
            if ending:
                extraDias+=1
            
            
    
    weekDays=["monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"]
    if (day!=None):
        day = weekDays.index(day.lower())
        day += extraDias
        day = weekDays[day%7].capitalize()
        
        
    
    #paso el ending a AM y PM para imprimirlo
    if (ending == True):
        ending = "AM"
    else:
        ending = "PM"
        
    #calculate days later
    daysLater = str()
    if (extraDias==1):
        daysLater = "next day"
    elif (extraDias>1):
        daysLater = f"{extraDias} days later"
    

    tiempoFinal = "{0}:{1:02d} {2}".format(horasFinal,minutosFInal,ending)
    
    if (day != None):
        tiempoFinal += f", {day}"
    
    if (extraDias > 0):
        tiempoFinal+= f" ({daysLater})"
    
    
    

    
    return tiempoFinal
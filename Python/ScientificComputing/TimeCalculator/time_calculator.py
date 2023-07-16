# FALTA ARREGLA EL TEMA DEL PARAMETRO OPCIONAL

def add_time(start, duration, day=""):

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
        # pedazo de codigo que me sirve para calcular el n days later
        if ((horasFinal == 12) and (not ending)):
            extraDias+=1
        # verifico que no me pase del 12 en las horas
        if (horasFinal==13):
            horasFinal = 1
            ending = not ending #cambio de AM a PM y viceversa
    
    weekDays={1:"Monday",2:"Tuesday",3:"Wednesday",4:"Thursday",5:"Friday",6:"Saturday",7:"Sunday"}
    if (day != ""):
        for key,value in weekDays.items():
            if  (value == day):
                day = key
        day = (day+extraDias)%7
        if(day==0):
            day+=1
        
        
    
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
    
    if (day != ""):
        tiempoFInal = "{0:02d}:{1:02d} {2} {3}".format(horasFinal,minutosFInal,ending,weekDays[day])
    else:
        tiempoFInal = "{0:02d}:{1:02d} {2} ({3})".format(horasFinal,minutosFInal,ending,daysLater)
    
    return tiempoFInal
    
   
    
        




    return 0
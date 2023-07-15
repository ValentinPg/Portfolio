def arithmetic_arranger(problems,solve = False):
    arranged_problems = str()
    primeraLInea = str()
    segundaLInea = str()
    separators = str()
    res = str()
    
    
    #guardamos la cantidad de problemas y checkeamos que la longitud no sea >5
    long = len(problems)
    if (long > 5):
        return "Error: Too many problems."
    
    #vamos a iterar por cada problema
    for problem in range(long):
        #separamos los operandos del problemas
        n1, op, n2 = problems[problem].split()
        
        #checkeamos que sea una suma o resta
        if ((op!="-") and (op!="+")):
            return "Error: Operator must be '+' or '-'."
        
        #probamos que sean numeros el n1 y el n2
        try:
            int(n1)
            int(n2)
        except:
            return "Error: Numbers must only contain digits."
        
        #checkeamos que los numeros sean de 4 digitos maximo
        if ((len(n1)>4) or (len(n2)>4)):
            return "Error: Numbers cannot be more than four digits."
        
        ###
    ### Terminadas las validaciones empezamos con el formateo ###
    
    #recorro todos los problemas y separo los operandos
    for problem in problems:
        n1 = problem.split(" ")[0]
        op = problem.split(" ")[1]
        n2 = problem.split(" ")[2]
        
        #me fijo si es una suma o resta
        if (op == "+"):
            result = (int(n1)+int(n2))
        else:
            result = (int(n1)-int(n2))
        
        #oobtengo el operando de mayor longitud
        maxLong = max(len(n1),len(n2))+2
        
        #separo en 4 variables, la fila de arriba, la del medio (numeros y op), el resultado y los '-'
        top = f"{n1}".rjust(maxLong)
        bottom = op + f"{n2}".rjust(maxLong-1)
        result = str(result).rjust(maxLong)
        separator = ""
        for _ in range(maxLong):
            separator += "-"
            
        #no quiero que en el ultimo caso me imprima espacios al final
        if problem != problems[-1]:
            primeraLInea += top + "    "
            segundaLInea += bottom + "    "
            separators += separator + "    "
            res += result + "    "
        else:
            primeraLInea += top
            segundaLInea += bottom
            separators += separator
            res += result
            
              
    #hay un parametro adicional que si esta en True quiero que me muestre el resultado, sino no
    if solve:
        arranged_problems = primeraLInea + "\n" + segundaLInea + "\n" + separators + "\n" + res
    else:
        arranged_problems = primeraLInea + "\n" + segundaLInea + "\n" + separators
    

    return arranged_problems
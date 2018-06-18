# UNIDAD 2:

### Ejercicio de cálculo térmico: (ver páginas 57 a 66 de apuntes U2)

Se tiene un circuito de control de un motor de 500W a 60 volts, que se manejará al 80% de su
potencia nominal (400W)con un mosfet IRFZ44N. Las condiciones ambientales son
Tamb_max=50ºC.

#### Calcular:

a) Temperatura que alcanzará la juntura del transistor sin disipador (si la temperatura escapa
de la Tj máx especificada en la hoja de datos no continuar el cálculo)

b) Disipador necesario (Rth_sa) para trabajar con un margen de 40ºC respecto a la máxima
temperatura de operación de la juntura. Seleccionar uno (con convección natural o forzada)

c) Repetir el cálculo para un control PWM, con frecuencia 100kHz (duty cycle hasta 100%)

### Resolución:

    Tmax = 175°C
    Tamb_max=50ºC

    Rds = 17.5mΩ
    Rjc = 1.5°C/W
    Rcd = 0.5°C/W
    Rja = 62°C/W

    A)

    I = W/V => 400/60 = 6.666A
    Wd = I²*Rds => 6.66²*17.5mΩ = 0.77W
    T = Wd*Rja = 48.12°C
    (La resistencia varía con la temperatura, por ende debemos iterar sobre la curva de Rds(T))
      -> Rds(48) = 1.2 => Rds = 1.2 * Rds = 21
      -> Wd = I²*Rds = Wd*1.2 = 0.924W => T = Wd*Rja = 57.288°C
      -> Rds(57.3) = 1.25 => T = 6.66² * 17.5mΩ * 1.25 * 62°C/W -> 60.15°C
      end

      RESPUESTA = Alcanzará ~60°C, no hace falta disipación.

    B)

    Tb = (175 - 40) = 135°C
    dT = Tb - Tamb_max = 85°C
    Rds(85) = 1.5
    -> Wd = 6.66²*1.5*17.5mΩ = 1.1666W

    Rtotal = Rjc + Rcd + Rsa(disipador)
    Rsa_necesaria = (dt / Wd) - (Rjc + Rcd) => Rsa = 70.86 °C/W

    RESPUESTA = No se precisa disipador Rja original = 62°C/W

    C)

    tr = 60ns = 60x10^-9s
    tf = 45ns = 45x10^-9s
    freq = 100kHz = 10us = 10x10^-6s
    Wd = (V * I) / 4 = 100W
    W_conmutación = Wd*(tr +tf)/freq = 1.05W

    W_total = Wd + W_conmutación = 1.166W + 1.05W = 2.216W

    Rsa_necesaria = (dt / W_total) - (Rjc + Rcd) => Rsa = 36.36°C/W
    
    RESPUESTA -> el disipador Snap On 5780 con flujo de aire forzado cumple con esta especificación.

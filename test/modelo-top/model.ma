[top]
components : peaje-delle peaje-au6 empalme
Out : autoOut sonda-pau6 sonda-pd sonda-61 sonda-62 sonda-d
In : autoAu6 autoDelle
link : autoAu6 autoIn@peaje-au6
link : autoDelle autoIn@peaje-delle
link : autoOut@empalme autoOut
link : sonda-61@empalme sonda-61
link : sonda-62@empalme sonda-62
link : sonda-d@empalme sonda-d
link : sonda@peaje-au6 sonda-pau6
link : sonda@peaje-delle sonda-pd
link : autoOut@peaje-delle autoA@empalme
link : stopA@empalme stop@peaje-delle
link : libreA@empalme libre@peaje-delle
link : autoOut@peaje-au6 autoB@empalme
link : stopB@empalme stop@peaje-au6
link : libreB@empalme libre@peaje-au6

[peaje-au6]
components : cola-pau6@Cola cabinas-pau6
out : autoOut sonda
in : stop libre autoIn
link : autoIn autoIn@cola-pau6
link : autoOut@cabinas-pau6 autoOut
link : stop stopIn@cabinas-pau6
link : libre libreIn@cabinas-pau6
link : sonda@cola-pau6 sonda
link : autoOut@cola-pau6 autoIn@cabinas-pau6
link : stopOut@cabinas-pau6 stop@cola-pau6
link : libreOut@cabinas-pau6 libre@cola-pau6

[cabinas-pau6]
components : acept-cabinas-pau6@Aceptador ret-cabinas-pau6@Retardador desp-cabinas-pau6@Despachador
in : autoIn libreIn stopIn 
out : autoOut libreOut stopOut sonda
link : autoIn autoIn@acept-cabinas-pau6
link : stopOut@acept-cabinas-pau6 stopOut
link : libreOut@acept-cabinas-pau6 libreOut
link : sonda@acept-cabinas-pau6 sonda
link : autoOut@acept-cabinas-pau6 autoIn@ret-cabinas-pau6
link : autoOut@ret-cabinas-pau6 autoIn@desp-cabinas-pau6
link : autoOut@desp-cabinas-pau6 autoOut
link : stopIn stopIn@desp-cabinas-pau6
link : libreIn libreIn@desp-cabinas-pau6
link : stopIn controlR@acept-cabinas-pau6
link : autoOut@desp-cabinas-pau6 controlA@acept-cabinas-pau6

[acept-cabinas-pau6]
preparacion : 00:00:00:100
capacidad : 15

[ret-cabinas-pau6]
tiempo : 00:00:15:00
distancia : 00:00:03:00
carriles : 15

[desp-cabinas-pau6]
preparacion : 00:00:00:100
random : yes

[cola-pau6]
carriles : 4
capacidad : 50000
preparacion : 00:00:00:200

[peaje-delle]
components : cola-delle@Cola cabinas-pd
out : autoOut sonda
in : stop libre autoIn
link : autoIn autoIn@cola-delle
link : autoOut@cabinas-pd autoOut
link : stop stopIn@cabinas-pd
link : libre libreIn@cabinas-pd
link : sonda@cola-delle sonda
link : autoOut@cola-delle autoIn@cabinas-pd
link : stopOut@cabinas-pd stop@cola-delle
link : libreOut@cabinas-pd libre@cola-delle

[cabinas-pd]
components : acept-cabinas-pd@Aceptador ret-cabinas-pd@Retardador desp-cabinas-pd@Despachador
in : autoIn libreIn stopIn 
out : autoOut libreOut stopOut sonda
link : autoIn autoIn@acept-cabinas-pd
link : stopOut@acept-cabinas-pd stopOut
link : libreOut@acept-cabinas-pd libreOut
link : sonda@acept-cabinas-pd sonda
link : autoOut@acept-cabinas-pd autoIn@ret-cabinas-pd
link : autoOut@ret-cabinas-pd autoIn@desp-cabinas-pd
link : autoOut@desp-cabinas-pd autoOut
link : stopIn stopIn@desp-cabinas-pd
link : libreIn libreIn@desp-cabinas-pd
link : stopIn controlR@acept-cabinas-pd
link : autoOut@desp-cabinas-pd controlA@acept-cabinas-pd

[acept-cabinas-pd]
preparacion : 00:00:00:100
capacidad : 8

[ret-cabinas-pd]
tiempo : 00:00:15:00
distancia : 00:00:01:00
carriles : 8

[desp-cabinas-pd]
preparacion : 00:00:00:100
random : yes

[cola-delle]
carriles : 3
capacidad : 50000
preparacion : 00:00:00:200

[empalme]
components : via-delle via-au61 via-au62 inter@Interseccion
out : stopA libreA stopB libreB sonda-61 sonda-62 sonda-d autoOut
in : autoA autoB
link : autoA autoIn@via-delle
link : stopOut@via-delle stopA 
link : libreOut@via-delle libreA 
link : sonda@via-delle sonda-d 
link : autoB autoIn@via-au61
link : stopOut@via-au61 stopB 
link : libreOut@via-au61 libreB 
link : sonda@via-au61 sonda-61 
link : autoOut@inter autoOut
link : autoOut@via-au61 autoIn@via-au62
link : stopOut@via-au62 stopIn@via-au61
link : libreOut@via-au62 libreIn@via-au61
link : autoOut@via-au62 autoB@inter
link : stopB@inter stopIn@via-au62
link : libreB@inter libreIn@via-au62
link : sonda@via-au62 sonda-62 
link : autoOut@via-delle autoA@inter
link : stopA@inter stopIn@via-delle
link : libreA@inter libreIn@via-delle

[inter]
preparacion : 00:00:04:000
reinicio : 00:00:00:010
carriles : 4

[via-delle]
components : acept-via-delle@Aceptador ret-via-delle@Retardador desp-via-delle@Despachador
in : autoIn libreIn stopIn 
out : autoOut libreOut stopOut sonda
link : autoIn autoIn@acept-via-delle
link : stopOut@acept-via-delle stopOut
link : libreOut@acept-via-delle libreOut
link : sonda@acept-via-delle sonda
link : autoOut@acept-via-delle autoIn@ret-via-delle
link : autoOut@ret-via-delle autoIn@desp-via-delle
link : autoOut@desp-via-delle autoOut
link : stopIn stopIn@desp-via-delle
link : libreIn libreIn@desp-via-delle
link : stopIn controlR@acept-via-delle
link : autoOut@desp-via-delle controlA@acept-via-delle

[acept-via-delle]
preparacion : 00:00:00:100
capacidad : 100

[ret-via-delle]
tiempo : 00:00:15:00
distancia : 00:00:01:000
carriles : 4

[desp-via-delle]
preparacion : 00:00:00:10
random : no

[via-au61]
components : acept-via-au61@Aceptador ret-via-au61@Retardador desp-via-au61@Despachador
in : autoIn libreIn stopIn 
out : autoOut libreOut stopOut sonda
link : autoIn autoIn@acept-via-au61
link : stopOut@acept-via-au61 stopOut
link : libreOut@acept-via-au61 libreOut
link : sonda@acept-via-au61 sonda
link : autoOut@acept-via-au61 autoIn@ret-via-au61
link : autoOut@ret-via-au61 autoIn@desp-via-au61
link : autoOut@desp-via-au61 autoOut
link : stopIn stopIn@desp-via-au61
link : libreIn libreIn@desp-via-au61
link : stopIn controlR@acept-via-au61
link : autoOut@desp-via-au61 controlA@acept-via-au61

[acept-via-au61]
preparacion : 00:00:00:100
capacidad : 400

[ret-via-au61]
tiempo : 00:00:30:00
distancia : 00:00:04:00
carriles : 4

[desp-via-au61]
preparacion : 00:00:00:100
random : yes

[via-au62]
components : acept-via-au62@Aceptador ret-via-au62@Retardador desp-via-au62@Despachador
in : autoIn libreIn stopIn 
out : autoOut libreOut stopOut sonda
link : autoIn autoIn@acept-via-au62
link : stopOut@acept-via-au62 stopOut
link : libreOut@acept-via-au62 libreOut
link : sonda@acept-via-au62 sonda
link : autoOut@acept-via-au62 autoIn@ret-via-au62
link : autoOut@ret-via-au62 autoIn@desp-via-au62
link : autoOut@desp-via-au62 autoOut
link : stopIn stopIn@desp-via-au62
link : libreIn libreIn@desp-via-au62
link : stopIn controlR@acept-via-au62
link : autoOut@desp-via-au62 controlA@acept-via-au62

[acept-via-au62]
preparacion : 00:00:00:100
capacidad : 300

[ret-via-au62]
tiempo : 00:00:40:00
distancia : 00:00:03:500
carriles : 3

[desp-via-au62]
preparacion : 00:00:00:100
random : yes

[top]
components : int@Interseccion da@Despachador db@Despachador
Out : autoOut 
In: autoA autoB

Link : autoA autoIn@da
Link : autoB autoIn@db
Link : autoOut@int autoOut

Link : autoOut@da autoA@int
Link : stopA@int stopIn@da
Link : libreA@int libreIn@da

Link : autoOut@db autoB@int
Link : stopB@int stopIn@db
Link : libreB@int libreIn@db

[int]
preparacion : 00:00:00:005
reinicio : 00:00:00:001
carriles : 4

[da]
preparacion : 00:00:00:005
random : yes

[db]
preparacion : 00:00:00:005
random : yes
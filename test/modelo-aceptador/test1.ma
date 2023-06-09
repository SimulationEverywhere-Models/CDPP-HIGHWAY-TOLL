[top]
components : model@Aceptador
Out : autoOut stopOut libreOut sonda
In: controlA controlR autoIn
Link : autoIn autoIn@model
Link : autoOut@model autoOut
Link : stopOut@model stopOut
Link : libreOut@model libreOut
link : sonda@model sonda


[model]
preparacion : 00:00:00:005
capacidad : 15

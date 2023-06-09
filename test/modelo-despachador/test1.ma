[top]
components : model@Despachador
Out : autoOut
In: stopIn libreIn autoIn
Link : autoIn autoIn@model
Link : autoOut@model autoOut
Link : stopIn stopIn@model
Link : libreIn libreIn@model

[model]
preparacion : 00:00:00:005
random : yes

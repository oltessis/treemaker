

#include "application.h"
#include "parameters.h"


int main()
{
    printf("main encountered");
    
    TreeParameters parameters;
    Application app; 
    app.run(parameters);

    return 0; 
}








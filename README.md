A not finished project trying to implement EAC into Battlefield 2. 

This is a kinda proof of concept and worked fine, since you can emulate the login services. 

Blame my sphagetti, let's make it public. 

Patch the Battlefield2.exe and force it to load the DLL at startup, so the whole process is protected. 


**If you take a look i'm patching sdkrevision parameter sent to the login services. Creating a secret and transfering it would be a save solution to check if the client actually loaded EAC at the login.**

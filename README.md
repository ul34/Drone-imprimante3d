# Drone-imprimante3d
P.I.D &amp; I3D

                                               Drone quadrimoteur en X.


- Drone Frame impression 3D 

-Quel type de plastique utiliser ?
   
Personnelement j'ai utiliser du PETG mais cela est une solution sous-optimal, le polypropylene plus difficille a imprimée, il         ne colle pas au surface type build-plate, verre. Le polypropylene ne colle que sur sur le polypropylene.
C'est désavantage et avantage sa résistance méchanique plus faible a l'étirement que la plus part des plastiques il posséde néanmoins une grande résistance au choque est une bonne flexibilité pour notre projet la résistance au choque est éssentielles. 
   

 
 
 - Paramétres impression 3D
 
-Surface d'impression minimale pour ce drone 180*180 mm.
 
-Température impression buse PETG : 245 C°
 
-Température impression plateau PETG : 80 C°
 
-Buse 0.6 mm
 
-Hauteur de couche 0.2 mm
 
Remarque: les températures d'impression varie en fonction de la marque de plastique utilisée.
 
 


- Fichier impression 3D

-Drone.montage.stl ce fichié n'est pas a imprimé il montre juste l'assemblage des différentes piéces.

-N.basdrone.stl ce fichié contient la piéce du bas du drone avec le support de batterie (l'orsque vous imprimerai cette piéce activer les supports).

-N.ruche.stl ce fichié contient la piéce du haut qui permet de fixer les bras du drone.Il faut que les losanges soit perpendiculaire au losange de la piéce du bas pour avoir une rigidité égale.

-N.bras.stl ce fichier permet d'imprimée les bras du drone duplique les au nombres de 4 dans votre slicer (Cura...).

-N.calibras.stl ce fichier permet d'imprimer des piéces aligne au millieux sur la longeur est la largeur.Elle permettra de glisser un rond de 6mm de diamétre pour pouvoir calibrer les coéfficients P.I.D des axes PITCH et ROLL.

-N.supMPU6050.stl ce fichier contient l'impression du support gyroscope, imprimé deux support.


- Materiel 

-MPU6050 *2 ~5€

-ESC 30A *4  ~20€

-arduino Uno ou arduino Mega

-Radiocommande Flysky fs-i6 avec récepteur  ~45€

-Moteur brushless BR2212 1000KV *4  ~20€

-Batterie 3S 11.1v ~30€

- Microcontroleur

L'arduino est un circuit électronique composer d'un microcontroleur que l'on peut appeler micro-ordinateur il possédent de la memoire morte reprogrammable (EPROM) de la mémoire vive et un processeur qui fait les calculs,il est doté d'entrée est de sortie, alors il peut communiquer de l'information sous forme électrique (OUTPUT) est recevoir de l'information (INPUT).
Il ya la partie alimentation composée d'un ou de plusieurs régulateur qui va limiter la tension a 5v est 3.3v avec des Condensateur est des résistances qui permettent de stabiliser la tension, un MiCro a besoin d'une alimentation trés stable pour fonctionner correctement. il ya aussi l'oscillateur qui permet au MiCro de se reperer dans le temps est determine aussi sa rapidité d'éxecution en HZ. Puis la derniere partie qui est un convertisseur USB::UART qui vous permet de televerser le programme dans le MiCro, mais pas que il permet aussi de recevoir des données pour voir si notre Prog est fonctionnel.
Résumons L'arduino est un MiCro "Plug&Play" qui va nous permettre de recevoir des donnés les transformés avec des calculs puis transmettre des données a des composants electronique. 

- Le gyroscope & accéléromètre

-Le MPU6050 est une centrale inertielle qui permet au microcontrolleur de connaitre la position du drone en degrés est la vitesse a laquelle il se déplace en degrés/S. Vous verrez plus tard qu'il est parametrable cela nous permettra de determiner une certaines plage de mesure ou activer des filtres.Il communiquera avec l'arduino via le protocole de communication nommé "I2C".








Frame impression 3D .

Controleur de vol P.I.D: arduino Uno ou arduino Mega. 
https://www.youtube.com/watch?v=yRw2mC_6A00


 
 ![alt tag](https://user-images.githubusercontent.com/52819943/78615340-866ab880-7871-11ea-9ce7-7f5a4f877526.png)
 
  
 
![alt tag]( https://user-images.githubusercontent.com/52819943/78615820-c67e6b00-7872-11ea-9dfd-4ab4ac3a28b6.png)

![alt tag](https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/%20MPU6050SHEMA.png)
 

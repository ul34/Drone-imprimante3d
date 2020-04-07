# Drone-imprimante3d
P.I.D &amp; I3D

                                               Drone quadrimoteur en X.


- Drone Frame impression 3D 

-Quel type de plastique utiliser ?
   
Personnelement j'ai utiliser du PETG mais cela est une solution sous-optimal, le polypropylene plus difficille a imprimée, il         ne colle pas au surface type build-plate, verre. Le polypropylene ne colle que sur sur le polypropylene.
C'est avantage sa résistance méchanique plus faible a l'étirement que la plus part des plastiques il posséde néanmoins une grande résistance au choque pour notre projet la résistance au choque est éssentielles. 
   

 
 
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





Frame impression 3D .

Controleur de vol P.I.D: arduino Uno ou arduino Mega. 



 
 ![alt tag](https://user-images.githubusercontent.com/52819943/78615340-866ab880-7871-11ea-9ce7-7f5a4f877526.png)
 
 
 
![alt tag]( https://user-images.githubusercontent.com/52819943/78615820-c67e6b00-7872-11ea-9dfd-4ab4ac3a28b6.png)

![alt tag](https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/%20MPU6050SHEMA.png)
 

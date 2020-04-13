# Drone-imprimante3d
P.I.D &amp; I3D

                                               DRONE QUADRIMOTEUR EN X.


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

-Hélices horaires * 2

-Hélices anti-horaires

- Microcontroleur

L'arduino est un circuit électronique composer d'un microcontroleur que l'on peut appeler micro-ordinateur il possédent de la memoire morte reprogrammable (EPROM) de la mémoire vive et un processeur qui fait les calculs,il est doté d'entrée est de sortie, alors il peut communiquer de l'information sous forme électrique(OUTPUT)est recevoir de l'information(INPUT).
Il ya la partie alimentation composée d'un ou de plusieurs régulateur qui va limiter la tension a 5v est 3.3v avec des Condensateur est des résistances qui permettent de stabiliser la tension, un MiCro a besoin d'une alimentation trés stable pour fonctionner correctement. il ya aussi l'oscillateur qui permet au MiCro de se reperer dans le temps est determine aussi sa rapidité d'éxecution en HZ. Puis la derniere partie qui est un convertisseur USB::UART qui vous permet de televerser le programme dans le MiCro, mais pas que, il permet aussi de recevoir des données pour voir si notre Prog est fonctionnel.
Résumons L'arduino est un MiCro "Plug&Play" qui va nous permettre de recevoir des donnés les transformés avec des calculs puis transmettre des données a des composants electronique. 

- Le gyroscope & accéléromètre

-Le MPU6050 est une centrale inertielle qui permet au microcontrolleur de connaitre la position du drone autour de trois axe X = ROLL, Y = PITCH, Z = YAW en degrés est la vitesse a laquelle il se déplace en degrés/S. Vous verrez plus tard qu'il est parametrable cela nous permettra de determiner une certaines plage de mesure ou activer des filtres.Il communiquera avec l'arduino via le protocole de communication nommé "I2C".

- ESC

-Les ESC sont des circuit électronique composer d'un MiCro avec un programme qui controle des transistor Mosfet qui on le role d'interrupteur pour pouvoir commuter le courant electrique est changer le sens du champ magnetique des bobines(situéés sur le stator) en fonction de la position du rotor constitué d'aimant, cette position est donner au MiCro via des capteurs a effet Hall ou dans notre situation la force contre électromotrice. Le MiCro peut alors suivre la sequence propre au moteur et le faire tourner, pour controler la vitesse de rotation le MiCro utilise le rapport cyclique(PWM) en controlant les interrupteur(Mosfet), pour vous donner un exemple imaginer une led avec un interrupteur que nous allumons 500ms puis eteignons 500ms est ainsi de suite nous avons alors un signaux cyclique puis qu'il se repete, on peut aussi determiner notre periode qui est de 1S imaginons maintenant que notre led consomme 1 w/h = 3600 joule soit  une consommation en énergie de 1 joule par seconde vu q'une heure est égale a 3600S donc si notre led est allumée en permanence elle consomme 1 joule/S mais nous  ne l'allumons que 50 % du temps donc la led recoit 50% de l'énergie quelle pourrait recevoir par apport au temps exemple sur 1h la led a consommée 1800J a la place de 3600J mais si vous faite cette expérience avec une periode aussi longue 1S vous verrez la led clignoter est ce n'est pas le but rechercher l'objectif est de pouvoir moduler la luminosite de la led pour cela il faut reduire la periode pour que l'allumage et l'extinction passe sous le seuil de perception visuelle(~100ms) exemple 10ms allumé 10Ums eteint plus la periode diminue plus la frequence est élever et cela necessite d'avoir des interrupteur qui peuvent commuter rapidement. Le calcul est le suivant (Rapport cyclique en % = durée allumé / durée période). Maintenant revenons a nos ESC plus la frequence "PWM" est élever plus la régulation de vitesse sera précise est constante, mais il faut alors un ESC avec des transistor de bonne qualité est capable de fonctionner a haute frequence pour notre premier drone ce préocuper de la frequence d'échantillonage na pas vraiment d'interet puisque nous utilisons des ESC bas de gamme.
Malgré ses explication nous ne savons toujour pas comment envoyer de l'information au MiCro des ESC pour qu'il puisse réguler la vitesse mais vous allez voir que ce n'est pas très difficille, c'est notre controleur de vol qui envoie l'information au ESC, nous allons envoyer l'information en controlant la largeur d'impulsion pour étre plus clair c'est le temps que le signaux réste a l'état haut(5v) a ce niveau la frequence n'est pas trés importante pour notre cas. En général la longueur d'impulsion varie entre 1000us ce qui signifie moteur a l'arrét est 2000us qui correspond au moteur a pleine puissancece ce qui fait "théoriquement" 1000 vitesse différente possible.

 





- Moteur brushless

-Ce sont des moteur électrique sans balais est collecteur car ses moteur peuvent avoir une vitesse de rotation trés élever ce qui augmente la durée de vie du moteur mais il faut en contrepartie un circuit electronique pour assurer le role des balais est collecteur, l'orsque vous acheté des moteurs de drone vous verrez des inscriptions il ya d'abord les dimensions du moteur puis une indication sur la vitesse de rotation en fonction du voltage, je vais vous donner un exemple "BR2212 1000KV" vous voyez le nombre 2212, composé de quatre chifre ?. Les deux premier chiffre "22" indique le diamétre du stator et les deux suivant représente la hauteur du stator "12". Les KV vous donnent la vitesse du moteur en fonction du voltage que vous lui donné, nous avons la un moteur "1000KV" si je lui donne 2V le moteur tournera alors a 2000 tour/minutes. Nous allons maintenant parler du fonctionnement d'un moteur brushless tout d'abord il existe deux variantes le Brushless in-runner ou le stator est en périphérie est le rotor est central et le out-runner avec le stator central est le rotor appelé "cloche" a l'exterieur cela permet d'avoir un couple plus important, plus le diamétre de la cloche est important plus vous aurez de couple ces moteur sont les plus utiliser dans le monde du drone je n'ai jamais vue un moteur in-runner sur un drone. 

Le rotor se compose d'aimant permanent avec un champ magnétique fixe, le stator est composer de bobines en changant le sens du courant on inverse les poles du champ magnétique rappeller vous que le NORD attire le SUD le SUD repousse le SUD est le NORD repousse le NORD, ses la que vient la notion de séquence pour faire tourner votre moteur il va falloir alimenter les bobines en inversant le sens du courant au bon moment afin que les champs magnétiques des bobines pousse et attire dans le sens voulu les aimants permanent pour crée une rotation. Une sequence se divise en plusieurs étapes qui se répéte, pour pouvoir connaitre la position du rotor est exécuter la bonne étapes on mesure le voltage de la bobine qui n'est pas alimenté, no moteur ont trois phase donc le nombre de bobines est un multiple de trois, imaginé un moteur avec trois bobines avec un point commun a chaque étapes on alimente deux bobines sur trois est on mesure le voltage de la bobine libre cette tension varie en fonction de la position de l'aimant permanent du rotor parapport a la bobine quand l'aimant est a 180° donc alignée avec la bobine la tension est nule ses ce que l'on appelle le "ZERO CROSS" qui permet au controleur de vitesse de savoir quand passer a l'étape suivante.


- Radiocommande & recepteur

-La radiocommande vous permez de déplacer le drone autour des trois axes ROLL,PITCH,YAW est de controler les GAZ. Le récepteur qui se trouve sur le dronne recoit les signaux de la télécommande et les transmets au controleur de vol.
Le recepteur communique avec le controleur de vol via des channels et nous allons en utiliser quatre car nous avons quatre commande différente ROLL,PITCH,YAW et GAZ, la méthode de communication entre le récepteur est notre controleur de vol est la méme que celle utilisée pour controler les ESC,le recepteur enverra l'information en faisant varier la largeur d'impulsion en fonction de notre commande entre 1000us et 2000us pour lires la largeur d'impulsion soit le temps ou l'impulsion reste a l'etat haut  nous allons utiliser les interruptions de l'arduino qui s'active a chaque changement d'état.

L'orsque vous achetez votre radiocommande vous devrez choisir votre configuration de commande appeller Mode cliquez sur l'image suivante pour voir ou se trouve les commandes du PITCH,ROLL,YAW,GAZ en fonction du Mode.


<img src="https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/Mode.png" width="200" height="125">





- Hélices

-Les hélices permettent a notre drone de se déplacer, elle pousse l'air a une grande vitesse derriére est nous avons depuis Newton que toute masse soumise a une force (action) oppose a celle si une force égale (contre-réaction) ce qui crée la poussée. Pour choisir ses hélices il ya plusieurs caractéristiques a prendre en compte.

-Le pas géométrique

Petit pas = plus grande traction à faible vitesse, mais vitesse maxi limitée.

Grand pas = plus petite traction à faible vitesse, mais vitesse maxi élevée.

-La taille des hélices

Grande Hélice = beaucoup de portance → vol stable mais a besoin de puissance pour faire 1 tour entier → moteur important.

Petite Hélice = peu de portance → vol moins stable et à besoin de moins de puissance pour faire 1 tour entier → moteur faible.

-Nombre de pales

 nombre de pales élevés = poussée plus élevée → rendement énergétique plus faible.
 
 nombre de pales faibles = poussée plus faible → rendement énergétique élevé.
 
 Pour augmenter la poussée vous pouvez augmentez la taille des hélices mais cela a ses limites vous risquez d'arracher le rotor de votre moteur ou  de crée une usure prématuré des roulements, pour notre drone prenez des hélices de "12" pouces maximum, personnellemnt j'utilise des hélices 1045 soit "10" pouces 25cm avec un pas de 4.5.
 
 
 - Montage composant & soudure
 
 
 Prennez votre radiocommande si vous avez une Flysky fs-i6 allumez la restez appuyez sur le bouton "OK" qui vous méne vers un menu avec deux sous menu "System setup" et "Functions setup" déplacer vous avec les touches "up" et "down" sur le sous menu "Functions setup" et cliquez sur "OK" puis déplacez vous sur "Display" est cliquez "OK" est la vous verrez vos channels. Bougez vos commandes est vous verrez quel commande correspond a quel channel. 
 
 RaDio Mode1 vous devriez avoir le "YAW" CH1, le "PITCH" CH2, les "GAZ" CH3, le "ROLL" CH4. Maintenat nous savons quel channel du recepteur transmet tel commande, si vous utilisez un arduino uno souder un fil de la CH1 du recepteur a la pin digital 8, CH2 a la pin digital 9, CH3 a la pin digital 11, CH4 a la pin digital 10. Si vous avez un arduino mega pro mini souder CH1 a la pin digital 53, CH2 a la pin digital 52, CH3 a la pin digital 50, CH4  a la pin digital 10.
 Si vous avez une RaDio Mode2 ou autre vos commande ne seront pas assigné au méme CH dites vous que pour l'arduino uno la pin digiital 8 doit recevoir du recepteur la commande du "YAW", la pin digital 9 le "PITCH", la pin digital 10 le "ROLL", la pin digital 11 les "GAZ" et pour l'arduino mega on suis la méme logique la pin digital 53 recoit le"YAW",pin digital 52 le "PITCH",pin digital 50 les "GAZ",pin digital 10 le "ROLL". SI vous vous trompez dans l'ordre des soudures ne vous embétés pas a dessouder nous verrons plus tard dans la partie programme comment changer l'assignation des pin.
 
 Maintenant nous passons au montage des deux gyroscopes tous d'abord imprimer les deux petits support qui se trouve dans le fichier "...." visé dessus les gyroscopes puis collé les deux support sur la plaque que vous avez imprimé avec le fichier "N.basdrone.stl". la position des GyRo sur la plaque n'est pas important mais le sens des gyroscopes doit étre respecté comme vous pouvais le voir sur l'image ci-dessous aidé vous en utilisant les petites fléches inscrites sur les GyRo.
 Maintenant passons au soudure tous dabord il faut souder un fil entre le "VCC" du MPU-2 et sa broche "ADO" puis relier le "VCC"
 des deux "MPU" sur le +3.3V de l'arduino, les deux "GND" sur le GND, les deux "SDA"(Serial data) sur "A4" les deux "SCL"(Serial clock line) sur "A5". Pour plus de solidité est éviter l'arrachement d'un fils réunissez les et faite une trésse.
 
 
  <img src="https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/DR.png" width="200" height="125">

 
 
 
 
 









https://www.youtube.com/watch?v=bCEiOnuODac

Frame impression 3D .

Controleur de vol P.I.D: arduino Uno ou arduino Mega. 
https://www.youtube.com/watch?v=yRw2mC_6A00


 
 
  
 <img src="https://user-images.githubusercontent.com/52819943/78615340-866ab880-7871-11ea-9ce7-7f5a4f877526.png" width="200" height="125">
 
  
  <img src="https://user-images.githubusercontent.com/52819943/78615820-c67e6b00-7872-11ea-9dfd-4ab4ac3a28b6.png" width="200" height="125">
  
   
   <img src="https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/%20MPU6050SHEMA.png" width="400" height="400">
 

 
 

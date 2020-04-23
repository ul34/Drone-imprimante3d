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

-Le MPU6050 est une centrale inertielle qui réuni gyroscope et accelerométre ce qui permet au microcontrolleur de connaitre la position du drone autour de trois axe X = ROLL, Y = PITCH, Z = YAW en degrés est la vitesse a laquelle il se déplace en degrés/S. Vous verrez plus tard qu'il est parametrable cela nous permettra de determiner une certaines plage de mesure ou activer des filtres.Il communiquera avec l'arduino via le protocole de communication nommé "I2C".

- ESC

-Les ESC sont des circuit électronique composer d'un MiCro avec un programme qui controle des transistor Mosfet qui on le role d'interrupteur pour pouvoir commuter le courant electrique est changer le sens du champ magnetique des bobines(situéés sur le stator) en fonction de la position du rotor constitué d'aimant, cette position est donner au MiCro via des capteurs a effet Hall ou dans notre situation la force contre électromotrice. Le MiCro peut alors suivre la sequence propre au moteur et le faire tourner, pour controler la vitesse de rotation le MiCro utilise le rapport cyclique(PWM) en controlant les interrupteur(Mosfet), pour vous donner un exemple imaginer une led avec un interrupteur que nous allumons 500ms puis eteignons 500ms est ainsi de suite nous avons alors un signaux cyclique puis qu'il se repete, on peut aussi determiner notre periode qui est de 1S imaginons maintenant que notre led consomme 1 w/h = 3600 joule soit  une consommation en énergie de 1 joule par seconde vu q'une heure est égale a 3600S donc si notre led est allumée en permanence elle consomme 1 joule/S mais nous  ne l'allumons que 50 % du temps donc la led recoit 50% de l'énergie quelle pourrait recevoir par apport au temps exemple sur 1h la led a consommée 1800J a la place de 3600J mais si vous faite cette expérience avec une periode aussi longue 1S vous verrez la led clignoter est ce n'est pas le but rechercher l'objectif est de pouvoir moduler la luminosite de la led pour cela il faut reduire la periode pour que l'allumage et l'extinction passe sous le seuil de perception visuelle(~100ms) exemple 10ms allumé 10Ums eteint plus la periode diminue plus la frequence est élever et cela necessite d'avoir des interrupteur qui peuvent commuter rapidement. Le calcul est le suivant (Rapport cyclique en % = durée allumé / durée période). Maintenant revenons a nos ESC plus la frequence "PWM" est élever plus la régulation de vitesse sera précise est constante, mais il faut alors un ESC avec des transistor de bonne qualité est capable de fonctionner a haute frequence pour notre premier drone ce préocuper de la frequence d'échantillonage na pas vraiment d'interet puisque nous utilisons des ESC bas de gamme.
Malgré ses explication nous ne savons toujour pas comment envoyer de l'information au MiCro des ESC pour qu'il puisse réguler la vitesse mais vous allez voir que ce n'est pas très difficille, c'est notre controleur de vol qui envoie l'information au ESC, nous allons envoyer l'information en controlant la largeur d'impulsion pour étre plus clair c'est le temps que le signaux réste a l'état haut(5v) a ce niveau la frequence n'est pas trés importante pour notre cas. En général la longueur d'impulsion varie entre 1000us ce qui signifie moteur a l'arrét est 2000us qui correspond au moteur a pleine puissancece ce qui fait "théoriquement" 1000 vitesse différente possible.

 





- Moteur brushless

-Ce sont des moteur électrique sans balais est collecteur car ses moteur peuvent avoir une vitesse de rotation trés élever ce qui augmente la durée de vie du moteur mais il faut en contrepartie un circuit electronique pour assurer le role des balais est collecteur, l'orsque vous acheté des moteurs de drone vous verrez des inscriptions il ya d'abord les dimensions du moteur puis une indication sur la vitesse de rotation en fonction du voltage, je vais vous donner un exemple "BR2212 1000KV" vous voyez le nombre 2212, composé de quatre chifre ?. Les deux premier chiffre "22" indique le diamétre du stator et les deux suivant représente la hauteur du stator "12". Les KV vous donnent la vitesse du moteur en fonction du voltage que vous lui donné, nous avons la un moteur "1000KV" si je lui donne 2V le moteur tournera alors a 2000 tour/minutes. Nous allons maintenant parler du fonctionnement d'un moteur brushless tout d'abord il existe deux variantes le Brushless in-runner ou le stator est en périphérie est le rotor est central et le out-runner avec le stator central est le rotor appelé "cloche" a l'exterieur cela permet d'avoir un couple plus important, plus le diamétre de la cloche est important plus vous aurez de couple ces moteur sont les plus utiliser dans le monde du drone je n'ai jamais vue un moteur in-runner sur un drone. 

Le rotor se compose d'aimant permanent avec un champ magnétique fixe, le stator est composer de bobines en changant le sens du courant on inverse les poles du champ magnétique rappeller vous que le NORD attire le SUD le SUD repousse le SUD est le NORD repousse le NORD, ses la que vient la notion de séquence pour faire tourner votre moteur il va falloir alimenter les bobines en inversant le sens du courant au bon moment afin que les champs magnétiques des bobines pousse et attire dans le sens voulu les aimants permanent pour crée une rotation. Une sequence se divise en plusieurs étapes qui se répéte, pour pouvoir connaitre la position du rotor est exécuter la bonne étapes on mesure le voltage de la bobine qui n'est pas alimenté, no moteur ont trois phase donc le nombre de bobines est un multiple de trois, imaginé un moteur avec trois bobines avec un point commun a chaque étapes on alimente deux bobines sur trois est on mesure le voltage de la bobine libre cette tension varie en fonction de la position de l'aimant permanent du rotor parapport a la bobine quand l'aimant est a 180° donc alignée avec la bobine la tension est nule ses ce que l'on appelle le "ZERO CROSS" qui permet au controleur de vitesse de savoir quand passer a l'étape suivante.


- Radiocommande & recepteur

-La radiocommande vous permez de déplacer le drone autour des trois axes ROLL,PITCH,YAW est de controler les GAZ. Le récepteur qui se trouve sur le dronne recoit les signaux de la télécommande et les transmets au controleur de vol.
Le recepteur communique avec le controleur de vol via des channels et nous allons en utiliser quatre car nous avons quatre commande différente ROLL,PITCH,YAW et GAZ, la méthode de communication entre le récepteur est notre controleur de vol est la méme que celle utilisée pour controler les ESC,le recepteur enverra l'information en faisant varier la largeur d'impulsion en fonction de notre commande entre 1000us et 2000us pour lires la largeur d'impulsion soit le temps ou l'impulsion reste a l'etat haut  nous allons utiliser les interruptions de l'arduino qui s'active a chaque changement d'état.

L'orsque vous achetez votre radiocommande vous devrez choisir votre configuration de commande appeller Mode cliquez sur l'image suivante pour voir ou se trouve les commandes du PITCH,ROLL,YAW,GAZ en fonction du Mode, la deuxiéme image représente le récepteur.

- RADIOCOMMANDE

<img src="https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/Mode.png" width="200" height="125">

- RECEPTEUR

<img src="https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/Recepteur.png" width="200" height="125">
 





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
 
 
  Si vous avez le matérielle nécessaire pour réaliser des circuit imprimée est vous voulez transferez le circuit sur la plaque en cuivre en utilisant de l'acetone et alcool ou en utilisant le transfert par chaleur avec un fer a repasse imprimée avec une imprimante laser les fichiers "PCB-FC.pdf" et "PCB-power distrib.pdf". Les deux autres fichier "PCB-FC-négatif.pdf" et "PCB-power distrib-négatif.pdf" sont utile si vous faites vos circuit imprimée avec une insoleuse. Si vous n'avez pas le materielle nécessaire suivez les instructions suivante.
  
 
 -Prennez votre radiocommande brancher le cable de bind si vous avez une Flysky fs-i6 allumez la et restez appuyez sur le bouton "Bind key" cela va permettre de crée la liaison entre la radiocommande est le recepteur puis restez appuyez sur le bouton "OK" qui vous méne vers un menu avec deux sous menu "System setup" et "Functions setup" déplacer vous avec les touches "up" et "down" sur le sous menu "Functions setup" et cliquez sur "OK" puis déplacez vous sur "Display" est cliquez "OK" est la vous verrez vos channels. Bougez vos commandes est vous verrez quel commande correspond a quel channel. 
 
 Si vous avez une RaDio Mode1 vous devriez avoir le "YAW" CH1, le "PITCH" CH2, les "GAZ" CH3, le "ROLL" CH4. Maintenant nous savons quel channel du recepteur transmet quel commande. 
 
  Si vous avez une RaDio Mode2 ou autre vos commande ne seront pas assigné au méme CH dites vous que pour l'arduino uno la pin digiital 8 doit recevoir du recepteur la commande du "YAW", la pin digital 9 le "PITCH", la pin digital 10 le "ROLL", la pin digital 11 les "GAZ" et pour l'arduino mega on suis la méme logique la pin digital 53 recoit le"YAW",pin digital 52 le "PITCH",pin digital 50 les "GAZ",pin digital 10 le "ROLL". Pour finir rendez vous dans le sous menu "Functions setup" rentrez dans Reverse et inverser la CH du "YAW" et du "PITCH". Si vous vous trompez dans l'ordre des soudures ne vous embétés pas a dessouder nous verrons plus tard dans la partie programme comment changer l'assignation des pin.
 
 
 
    -ARDUINO UNO.
 
    le + du recpteur au +5v

    le _ du recepteur au gnd
 
    CH1"YAW" du recepteur a la pin digital 8. 

    CH2"PITCH" a la pin digital 9. 
  
    CH3"GAZ" a la pin digital 10. 
 
    CH4"ROLL" a la pin digital 11. 
 
    
    -ARDUINO MEGA PRO MINI.
 
    le + du recpteur au +5

    le _ du recepteur au gnd
 
    CH1"YAW" a la pin digital 53. 
 
    CH2"PITCH" a la pin digital 52. 
 
    CH3"GAZ" a la pin digital 50. 
 
    CH4"ROLL"  a la pin digital 10.
 

-Maintenant nous passons au montage des deux gyroscopes tous d'abord imprimer les deux petits support qui se trouve dans le fichier "...." visé dessus les gyroscopes puis collé les deux support sur la plaque que vous avez imprimé avec le fichier "N.basdrone.stl". la position des GyRo sur la plaque n'est pas important mais le sens des gyroscopes doit étre respecté comme vous pouvais le voir sur l'image ci-dessous aidé vous en utilisant les petites fléches inscrites sur les GyRo.
  
  <img src="https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/DR.png" width="200" height="125">
 
  passons au soudure tous dabord il faut souder un fil entre le "VCC" du MPU-2 et sa broche "ADO" puis relier le "VCC"
 des deux "MPU" sur le +3.3V de l'arduino, les deux "GND" sur un GND, les deux "SDA"(Serial data) sur "A4" les deux "SCL"(Serial clock line) sur "A5". Pour plus de solidité est éviter l'arrachement d'un fils réunissez les et faite une trésse.
 
 
  -Il reste alors les ESC a installée est a racorder a l'arduino, regarder l'image ci-dessous est vous verrez les deux fils d'alimentation (+12v,-) le fils signaux avec son gnd puis les trois fils moteur, rappeller vous nos moteur on trois phases et tous les moteurs de notre drone ne tourne pas dans le méme sens regarder de nouveau l'image ou il ya les deux gyroscopes vous verrez quel moteur tourne dans quel sens, horaire ou anti-horaire. Pour inverser le sens d'un moteur il suffit d'inverser le branchement des fils moteur. Maintenant nous allons souder aux arduino les fils du signaux de chaque ESC . 
  
    -ARDUINO UNO.
  
    ESC.moteur1 a la pin digital 4 
  
    ESC.moteur2 a la pin digital 5 
  
    ESC.moteur3 a la pin digital 6 
  
    ESC.moteur4 a la pin digital 7  
  
    -ARDUINO MEGA PRO MINI.  
  
    le ESC.moteur1 a la pin digital 26 
  
    le ESC.moteur2 a la pindigital 27 
  
    le ESC.moteur3 a la pin 28 
  
    le ESC.moteur4 a la pin 29 
  
    Reliez tous les gnd des signaux au gnd de l'arduino.
  
Pour alimenter les quatre ESC il faut fabriquer une "Power distribution board" on va faire un circuit imprimée comme sur l'image ci-dessous, prenez votre plaque de cuivre est un marqueur indélébile est redessiner les partie en rouge puis tremper la plaque de cuivre dans une solution de perchlorure de fer est agiter doucement il devrait rester que les parties colorier, les deux rectangle et le diviseurs de tension , mes a quoi le diviseur de tension peut il  servir ? l'arduino ne peut mesurer que des tensions inferieur ou égale a 5v notre batterie fait 12.6v pour pouvoir mesurer le niveau de charge de notre batterie et compenser la puissance des moteurs quand le voltage diminue, pour éviter d'avoir des commandes de moins en moin réactive au fils du vol il faut que l'arduino puisse mesurer le voltage alors nous méttons une diode avec deux resistances en serie est nous soudons un fil entre les deux resistances que nous relions a la pin analogique 0 . 

Et voici le calcul qui nous permet de connaitre la valeur de "R1 = (U/U2)*R2-R2"  je choisi une valeur de resistance arbitraire pour R2 elle doit tous de méme étre assez élever pour que notre circuit ne consomme pas trop de courant (I = U/R) on va prendre une valeur de 1000 Ohm, U represente la valeur de notre alimentation "12.6v", U2 la tension que l'on veut entre R1 et R2 donc 5v "R1=1520 =(12.6/5)*1000-1000" donc pour que U2 ou la broche Analogique 0 soit a 5v quand la batterie est a sa tention maximale il faut que R1 soit égale a 1520 Ohm, nous mettons une Resistance de 1.5k les 20 Ohm supplementaire n'ont pas un effet significatif et R2 1000 Ohm.

Conseil: l'orsque vous souderé la power distribution n'hésitez pas a mettre une couche d'etein sur les pistes avec les huit trous pour alimenter vos ESC il peut passer dans ces pistes un courant de 60 amperes et risque de crée une surchauffe.


 <img src="https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/PBD.png" width="200" height="125">
 
 - Programme
 
 -Le fichier "ESCALIB.ino" va nous permettre de calibrer les ESC , une fois le programme televerser ouvré le Serial  taper "1" puis "Entrée", branchez la batterie puis taper "0" la vous entendrez trois "beep" cela signifie que votre batterie est une 3S pour finir rentrer "2" dans le Serial, vous verrez vos moteur montez en puissance jusqu'a leur puissance maximale puis ils éteignent . Si vous avez l'aruino mega pro mini il faut changer la declarations des pin en mode OUTPUT "DDRD |= B11110000;" en  "DDRA  |= B11110000;" et changer toutes l'activation des pins a l'état haut "PORTD |= mot;" en "PORTA |= mot;" et a l'etat bas 
 "PORTD &=  B00000000;" en "PORTA &=  B00000000;"
 
 
 Que fait notre programme ESCALIB.ino ?
 
 L'orsque vous rentrez  "1" l'arduino envoie au ESC  chaque 8ms une impulsion de 2000us qui est la valeur maximaxe ce qui va mettre l'ESC en mode programmation puis quand on rentre "0" l'arduino envoie des impulsions de 1000us ce qui indique au ESC quel largeur d'impulsion est égale au moteur eteint, donc 2000us est égale a la vitesse maximale et 1000us au moteur eteint. Puis quand on rentre "2" on incremente une valeur a l'impulsion minimale j'usqu'a ateindre sa valeur maximale puis on retourne a une l'argeur d'impulsion de 1000us. 
 
 
 -Maintenant que nous avons nos ESC calibré rendez vous sur ce lien https://github.com/jrowberg/i2cdevlib est télécharger les fichier, dans tous ces fichier il ya deux bibliothéque qui nous intéresse "I2Cdev.h" et MPU6050.h une fois que vous les avez intégré dans votre IDE, télecharger le programme ecrit par Luis RODENA qui se trouve dans le fichier "...." qui va nous permettre de calibrer nos deux Gyro. 
 
 
 Pour le faire il faut d'abord bien positionner votre drone a plat en  utilisent un niveau a bulle, une fois qu'il est bien a plat on va pouvoir televerser le programme dans notre arduino. Mais nous avons deux Gyro a calibrer nous allons les calibrer un a la fois pour savoir lequel des deux nous sommes entrein de calibrer il faut connaitre l'adresse de chaque Gyro notre MPU-1 a pour adresse "0x68" et MPU-2 "0x69". Regarder le programme vous verrez cette ligne "MPU6050 accelgyro(0x69);" pour pouvoir changer de Gyro il suffit de changer l'adresse qui est entre parenthése par l'adrresse de votre Gyro.
 
 
 Une fois que vous avez choisi l'adresse téleverser le programme, pour le lancer ouvré le Serial  est rentré un caractére au hasard aprés une trentaine de seconde vous verrez apparaitre une ligne avec ecrit "Sensor readings with offsets" suivie de six nombre qui doivent etre proche de la suite suivante "0 0 16384 0 0 0",la ligne suivante ou il ya ecrit "Your offsets" suivie de six nombre "-3771 -1100 1106 -10 70 -8" se sont vos valeurs de calibration pour les trois axes de l'accelerométre est les trois axes du gyroscopes. Faites cette opération pour les deux Gyro puis ouvrez le fichier "...." si vous utilisez l'arduin uno ou "...." pour l'arduino mega pro mini est remplacer les six valeurs suivante pour chaque Gyro par vos valeurs d'offset.  
 
 
    mpu.initialize(); //MPU-1 = 0x68
  
    mpu.setXAccelOffset(-3771);
  
    mpu.setYAccelOffset(-1100);
 
    mpu.setZAccelOffset(1106);
  
    mpu.setXGyroOffset(-10);
  
    mpu.setYGyroOffset(70);
  
    mpu.setZGyroOffset(-8);
  
    mpu1.initialize(); //MPU-2 = 0x69
  
    mpu1.setXAccelOffset(497);
  
    mpu1.setYAccelOffset(1703);
  
    mpu1.setZAccelOffset(1148);
  
    mpu1.setXGyroOffset(-629);
  
    mpu1.setYGyroOffset(206);
  
    mpu1.setZGyroOffset(-8);
  
  
  Normalement apres avoir televerser le programme "....." votre dronne est prét a voler.
  
  
  
  - Explication Programme
  
  Notre programme recoit les commandes ordonné par notre radiocommande qui lui donne un angle a atteindre (Consigne) est les donnés du gyroscopes qui lui donne sa position actuelle est a la vitesse a laquelle le drone se déplace autour de ses trois axes,pour que le drone suive la consigne quon lui donne nous allons utiliser un régulateur P.I.D qui en fonction de la vitesse de déplacement du drone de sa position et de la consigne va distribuer la puissance des moteurs pour atteindre la consigne.
  
  
  -lecture des données recus par le recepteur
  
  
  Pour calculer l'angle a atteindre il faut d'abord lire la largeur d'impulsion de chaque CH rappeller vous on en a parler dans la partie " Radiocommande & recepteur" pour lire la largeur on va utiliser les interruptions en mode "Changes" ce qui veut dire quells activent l'orsque l'état de la CH passent de l'etat haut(5v) a bas(0v) ou de bas a haut.  Quand une interruption s'activent elle est prioritaire sur notre programme et lance une routine execution qui va faire les calculs pour connaitre la largeur d'impulsion. Une fois que le code de la routine est executer le programme reprend ou il ces arrété, si le code de la routine est trop volumineux votre programme ne fonctionnera pas car elle sera réappeller alors que l'execution du code n'est toujour pas finit.
  

Pour pouvoir les utiliser il faut declarer les interruptions le code suivant indique a l'arduino uno que les pins digital 8,9,10,11  vons etre uitliser comme interruptions en modes "Changes".  
   
     //N°bit = 76543210   //table de vérité "ou" = "1&0=1" "0&0=0" "1&1=1 
   
   
    //PCIRC = 00000000;
   
   
    //PCMSK0 = 00000000;
   
   
    PCICR  |= (1 << PCIE0); //PCIRC = 00000001; on met le bit 0 du registre PCICR a 1 
   
   
    PCMSK0 |= (1 << PCINT0); //PCMSK0 = 00000001; on met le bit 0 du registre PCMSK0 a 1 Pin digital 8
   
   
    PCMSK0 |= (1 << PCINT1); //PCMSK0 = 00000011; on met le bit 1 du registre PCMSK0 a 1 Pin digital 9
   
   
    PCMSK0 |= (1 << PCINT2); //PCMSK0 = 00000111; on met le bit 2 du registre PCMSK0 a 1 Pin digital 10
   
   
    PCMSK0 |= (1 << PCINT3); //PCMSK0 = 00001111; on met le bit 3 du registre PCMSK0 a 1 Pin digital 11
   

Pour bien comprendre le fonctionnement il faut imaginer un octet superposer a un autre octet ces pour sa que le "ou" est un comparateur de bit je vais donner des exemples
   
   
   
   
   
   
    PCMSK0 = 00000000; // le registre PCMSK0 se représente sur un octet 
   
   
    l'orsque nous faisons |= (1 << PCINT0) il se passe la chose suivante nous créons un octet et nous faisons se décaler vers la     gauche la valeur 1 de 0 bit "00000001" et on compare notre octet a l'octet du registre PCMSK0.
    
    
    PCMSK0 = 00000000;
                 
                 
                 |=          PCMSK0 =  00000001;
            
            
            00000001;
     
    l'orsque nous faisons |= (1 << PCINT1) il se passe la chose suivante nous créons un octet et nous faisons se décaler vers la     gauche la valeur 1 de 1 bit "00000010" et on compare notre octet a l'octet du registre PCMSK0.
             
    
    PCMSK0 = 00000001;
                 
                 
                 |=          PCMSK0 =  00000011
             
             
             00000010;
             
             
             
             
             
Maintenant que nous avons déclarée nos interruptions au pins 8,9,10,11 nous pouvons allez dans notre routine d'execution et taper notre code pour calculer la largeur d'impulsion.


     ISR(PCINT0_vect) //routine execution qui s'activent a chaque changement d'etat
     {
    current_time = micros(); // on lance un timer et on stoke T0

     
    if (PINB & B00000001) {  // SI pin digital 8 est a l'etat haut on execute le code entre les accolades                                       
        if (previous_state[0] == LOW) { // Si la variable previous_state[0] est égale a LOW                 
            previous_state[0] = HIGH;  // previous_state[0] est égale a HIGH                      
            timer[0]          = current_time; // on stoke T0 dans  timer[0]              
        }
    } else if(previous_state[0] == HIGH) { // SI pin 8 a l'etat haut est faut et que previous_state[0]==HIGH              
        previous_state[0] = LOW;  // previous_state[0] est égale a LOW                              
        pulse_duration[0] = current_time - timer[0]; Durée a l'état haut T1-T0 
    }
    }
    
 Pour bien comprendre imaginés que la pin D8 est a l'état bas(LOW) quand on allume le drone la pin D8 passe a l'état haut alors la routine d'execution s'activent on stoke dans la variable "current_time" le temps actuelle prenont une valeur arbitraire a titre d'exemple "current_time = 1000us" aprés nous testons une condition Si pin D8 est a l'etat haut on execute le code entre les accolades dans ces accolades il ya un autre test de condition Si la variable "previous_state[0]" est a l'etat bas et elle les car nous venons juste d'allumer l'arduino est la variable est initialiser a 0 soit etat bas on passe alors "previous_state[0]" a l'etat haut et on stoke le temps actuelle dans timer[0] soit 1000us,  le prochain test de condition "else if(previous_state[0] == HIGH)" est faux et n'execute pas le code entre les accollades car les test de condition est fault car "if (PINB & B00000001)" est vrai. Puis nous sortons de la routine d'exe est l'arduino recommence a executer le code la ou il c'était arrété. L'orsque la pin D8 change d'etat a nouveau sa veut dire pour nous quel va passer de l'état haut a l'etat bas la routine exe se relance on stoke comme a chaque nouvelle rentré dans la routine le temps actuelle dans "current_time = 2500us" cette fois si la condition "if (PINB & B00000001)" est fausse donc le code entre les accolades ne s'execute pas mais la condition "else if(previous_state[0] == HIGH)" est vrai car la premiere condition est fausse est "previous_state[0]" avais été mis a l'etat haut "HIGH" alors on execute le code entre accolades on repasse  "previous_state[0]" a l'etat bas "LOW" est ont soustrait le temps stoker dans "timer[0] = 1000us" l'or de la premiére activation de la routine au temps actuelle soit "current_time = 1500us" ce qui fait "pulse_duration[0] = 2500-1000;", maintenant nous pouvons connaitre la largeur d'impulsion de chaque CH ROLL, PITCH, YAW, GAZ.
 
 
 
 Rappelez vous notre recepteur envoie a notre controleur de vol des largeurs d'impulsion entre 1000us et 2000us l'orsque vous ne touchez pas les commandes du PITCH, ROLL, YAW de votre radiocommande la largeur d'impulsion est de 1500us ce qui veut dire que vous demandez a votre drone d'étre a plat "PITCH = 0°, ROLL = 0°, YAW = 0°/S" pour les GAZ 1000us signifie GAZ = minimum et 2000 us GAZ = maximum. Maintenant nous allons voir le code qui permet de transformez les largeurs d'impulsions en consigne.
 
 
     void consigne(){
  
           ConsG = 0; // A chaque boucle du programme on met la variable ConsG = "GAZ" a 0
          ConsP = 0;  // A chaque boucle du programme on met la variable  ConsP = "PITCH" a 0
          ConsR = 0; // A chaque boucle du programme on met la variable  ConsR = "ROLL" a 0
         ConsY = 0; //  // A chaque boucle du programme on met la variable  ConsY = "YAW" a 0
  
    chanel1 =  pulse_duration[2]; // on stoke la largeur d'impulsion CH "GAZ" dans la variable chanel1 
    chanel2 =  pulse_duration[1]; // on stoke la largeur d'impulsion CH "PITCH" dans la variable chanel2 
    chanel3 =  pulse_duration[3]; // on stoke la largeur d'impulsion CH "ROLL" dans la variable chanel3 
    chanel4 =  pulse_duration[0]; // on stoke la largeur d'impulsion CH "YAW" dans la variable chanel4
  
    if (chanel1 < 1000) chanel1 = 1000; // on limite les valeurs entre 1000 et 2000
     if (chanel1 > 1800) chanel1 = 1800;
     if (chanel2 < 1000) chanel2 = 1000;
     if (chanel2 > 2000) chanel2 = 2000;
    if (chanel3 < 1000) chanel3 = 1000;
    if (chanel3 > 2000) chanel3 = 2000;
    if (chanel4 < 1000) chanel4 = 1000;
    if (chanel4 > 2000) chanel4 = 2000;
    
  
  
  Maintenant qu'on a stoké les valeurs du "PITCH, ROLL, YAW, GAZ" est qu'on a limité les valeurs dans un intervalle [1000;2000]  on va séparé les intervalles en deux parties " ROLL = [1000<=gauche<1500>droite<=2000], PITCH = [1000<=avant<1500>arriére<=2000] , YAW = [1000<=droite<1500>gauche<=2000] pour les GAZ nous n'avons pas besoins de separer en deux l'intervalle. Comme le signal a du bruit il n'est pas parfaitement constant a 1500 ces pour ca que nous laisons une marge de 16us.
  
  
    //gaz
    if (chanel1 >1008){ // Si strictement plus grand que 10008 allumage des moteurs
    ConsG = chanel1;
     }
     
  
    //Pitch
    if (chanel2 >1508){ // SI strictement plus grand que 1508 "PITCH" vers l'arriére arriére
     ConsP = (chanel2-1508);
     }else if (chanel2 < 1492){ //sinon SI strictement plus petit que 1492 "PITCH" vers l'avant
     ConsP = (chanel2-1492);
     }
    
      //Roll
    if (chanel3 >1508){ // SI strictement plus grand que 1508 "ROLL" vers la droite 
     ConsR = (chanel3-1508);
     }else if (chanel3 < 1492){ //sinon SI strictement plus petit que 1492 "ROLL" vers la gauche
     ConsR = (chanel3-1492);
     }
     
       //Yaw
    if (chanel4 >1508){ // SI strictement plus grand que 1508 "YAW" vers la  gauche 
     ConsY = (chanel4-1508);
     }else if (chanel4 < 1492){  //sinon SI strictement plus petit que 1492 "YAW" vers la droite
     ConsY = (chanel4-1492);
     }
     
     
     
   Si sur votre radiocommande vous poussez le stick du Roll sur la droite et que la largeur d'impulsion dépassent 1508, on soustrait 1508 a la valeur recu ce qui nous donne une  Consigne qu'il faut convertir en angle a atteindre et nous savons que la largeur d'impulsion et au maximum 2000us il faut alors definir quel angle correspond a 2000us sa sera l'inclinaison maximale du drone.  Imaginez maintenant que vous poussez le stick du ROLL a droite en bout de course "chanel3 = 2000" ce qui fait      "ConsR = 2000-1508 = 492" est nous voulons que cette valeur représente 30.75° alors il faut que quand notre gyroscope indique 30.75°, ConsR soit égale a 0 alors si notre drone a une inclinaison de 30.75° il faut que l'angle soit multiplier par un coefficient et que le produit de cette multiplication soit égale a 492. Voici le calcul "492/Anglemax = coefficient"  si dessous vous avez un exemple les variables anglemaxP et  anglemaxR   stocke le  produit des multiplication entre les coefficients est l'angle actuelle pour l'axe du "ROLL" et du "PITCH" puis on soustrait les produit aux consigne et enfin on divise par trois pour limiter la vitesse de déplacement autour des axes a 164 °/S "492/3 = 164". Pour l'axe du "YAW" on ne fixe pas d'angle maximale mes une vitesse de deplacement maximale. 
   
   
     anglemaxP = 16 * angleP; // 2000-1508 = 492 , 492/16 = 30.75°, 492/30.75 = 16
     anglemaxR = 16 * angleR;
      
      ConsP -= anglemaxP ;
      ConsP /= 3;  // limitation de la vitesse de deplacement a 164°/S "492/3=164"
      ConsR -=  anglemaxR;
      ConsR /= 3;
      ConsY /= 3;
      
      
 Maintenat que nous avons les consignes de nos trois axes nous allons utiliser un régulateur P.I.D pour controler la position du drone mais d'abord je vais vous expliquer le fonctionnement de ce régulateur.
 
   le régulateur P.I.D va calculer les erreurs Proportionnelle.intégrale.Dérivée entre les Consignes et les mesures du Gyro pour chaque axe, et ont multiplie chaque erreurs par un coefficient puis on fait la sommme des trois erreurs qui sera notre commande a envoyer au moteur, chaque erreur na pas les mémes effets sur notre systéme.
 
 -L'erreur Proportionnelle correspond a l'écart entre la valeur mesurée et notre Consigne, cette ecart est multiplié par un coefficient plus il est grand plus votre systéme atteindra sont objectif rapidement mais un coeff trop grand crée des oscillations qui destabilise votre systéme, un coeff trop petit ne nous permettra pas d'atteindre l'objectif il faut alors trouver un bon compromis entre la vitesse pour atteindre l'objectif et de trop grand dépassement. Si nous utilisons seulement l'erreur proportionnelle le systéme oscilleré et n'arriverais pas a se stabiliser dans le temps sur l'objectif(Erreur statique).
 
 -L'erreur intégrale fait la somme des erreurs Prop au fil du temps cette erreur est complementaire a l'erreur Prop elle permet de reduire l'erreur statique dans le systéme si le coeff de l'erreur intégrale est trop élever cela crée  des oscillation est des grands dépassement de la consigne si il est trop faible votre systeme derivera est ne maintiendra pas l'objectif.
 
 -L'erreur dérivé, soustrai l'erreur Prop précédente a l'erreur Prop actuelle elle permet a notre systéme d'anticiper les déplacements donc dévité les dépassements de consigne si votre coeff dérivé est trop élevé vous verrez votre systéme oscillé a haute fréquence si il est trop bas il y aura des dépassements de consigne important.
 
 Si vous voulez voir les differents effets des coefficiens des erreurs "Prop,Int,Dev" regardez cette video :https://www.youtube.com/watch?v=uXnDwojRb1g.
 
 Sur votre banc de test faite varier les coefficient en fonction de vos préférence.
     
     
     float KYP = 6; // Coefficient Erreur Prop "YAW"
     float KYI = 0.22; // Coefficient Erreur intégrale "YAW"
     float KYD = 0; // Coefficient Erreur dérivé "YAW"

     float KRP = 1.3; // Coefficient Erreur Prop "ROLL"
      float KRI = 0.04; // Coefficient Erreur integrale "ROLL"
      float KRD = 18; // Coefficient Erreur dérivé "ROLL"

     float KPP = 1.3; // Coefficient Erreur Prop "PITCH" 
      float KPI =0.04; // Coefficient Erreur intégrale "PITCH"   
     float KPD = 18; // Coefficient Erreur derivé "PITCH"
 
     void PID(){

     
      
      EpropP = ASP - ConsP; //erreur proportionnelle "PITCH"
      EpropR = ASR - ConsR; //erreur proportionnelle "ROLL"
      EpropY = ASY - ConsY; //erreur proportionnelle "YAW"
 
 
      
      
      EintP +=  EpropP; //erreur intégrale "PITCH"
      EintR +=  EpropR; //erreur intégrale "ROLL" 
      EintY +=  EpropY; //erreur intégrale "YAW"
 
     if ( EintP > 400 ) EintP = 400; // on limite les valeurs de l'intégrale pour éviter d'avoir des valeurs disproportionner                                                              
     if ( EintP < -400 )EintP = -400;   qui engendrerées des dépassement effet "WindUp"
     if ( EintR > 400 ) EintR = 400;
     if ( EintR < -400 )EintR = -400;
     if ( EintY > 400 ) EintY = 400;
     if ( EintY < -400 )EintY = -400;
 
      
     EdevP =  EpropP-lastEP;  //erreur derivée "PITCH"
     EdevR =  EpropR-lastER; //erreur derivée "ROLL"
     EdevY =  EpropY-lastEY; //erreur derivée "YAW"
 
   
     lastEP =  EpropP; // On stoke l'erreur précédente du "PITCH"
     lastER =  EpropR; // On stoke l'erreur précédente du "ROLL"
     lastEY =  EpropY; // On stoke l'erreur précédente du "YAW"

 
   
     
    EPIDR = KRP * EpropR + KRI * EintR + KRD * EdevR; // Somme des erreurs pour l'axe du "ROLL"
    EPIDP = KPP * EpropP + KPI * EintP + KPD * EdevP; // Somme des erreurs pour l'axe du "PITCH"
    EPIDY = KYP * EpropY + KYI * EintY + KYD * EdevY; // Somme des erreurs pour l'axe du "YAW"

  
     if ( EPIDP > 400 ) EPIDP = 400; // on limite les valeurs de sortie pour quel reste coherente avec les valeurs que l'on 
     if ( EPIDP < -400 )EPIDP = -400;   enverra au moteur
     if (EPIDR > 400 ) EPIDR = 400;
     if (EPIDR < -400 )EPIDR = -400;
     if ( EPIDY > 400 ) EPIDY = 400;
     if ( EPIDY < -400 )EPIDY = -400;
 
}


Maintenant on va voir la partie du code qui va nous permettre de distribuer la puissance a chaque moteur.

     mot1 = ConsG-EPIDR-EPIDP-EPIDY;
     mot2 = ConsG+EPIDR-EPIDP+EPIDY;
     mot3 = ConsG-EPIDR+EPIDP+EPIDY;
     mot4 = ConsG+EPIDR+EPIDP-EPIDY;
     
     
 On rajoute la consigne GAZ a tous les moteur et nous soustrayons ou additionnons les sorties du controleur PID en fonction du signe de ses sorties, pour comprendre le mieux est de voir des exemples.
 
 Imagines votre drone qui se deplace autour de l'axe du "PITCH" vers l'avant a une vitesse de -10°/S est que votre Consigne est   égale a 0 donc votre programme doit monter la puissance des deux moteur a l'avant "mot1, mot2" et baisser la puisssance des moteurs arriéres "mot3, mot4". Le regulateur PID fait ce calcul "EpropP =-10-0" la valeur de sortie et négative -10 alors il faut que l'orsque j'ajoute -10 au "mot1, mot2" la valeur doit étre positive + 10 et restez négative pour "mot3, mot4", pour que sa soit positif il suffit de mettre - car "0--10" = +10 est mettez + pour que la valeur se soustrai "0+-10 = -10".
 
 Exemple Détaillé.
 
 KPP = 1;
 KPI = 1;
 KPD = 1
 
  anglemaxP = 16 * angleP; // -32 = 16*-2;
  ConsP -= anglemaxP ; // 32 = 0--32;
  EpropP = ASP - ConsP; // -42 = -10-32;
  EintP +=  EpropP; // -42 = 0 + -42;
  EdevP =  EpropP-lastEP;  -42 - 0;
  EPIDP = KPP * EpropP + KPI * EintP + KPD * EdevP; // -126 = 1 * -42 + 1 * -42 + 1 * -42;
  
   mot1 = ConsG-EPIDR-EPIDP-EPIDY; //1326 = 1200 - 0 --126 - 0;
   mot2 = ConsG+EPIDR-EPIDP+EPIDY; // 1326 = 1200 + 0 --126 + 0; 
   mot3 = ConsG-EPIDR+EPIDP+EPIDY; // 1074 = 1200 - 0 +-126 + 0;
   mot4 = ConsG+EPIDR+EPIDP-EPIDY; // 1074 = 1200 + 0 +-126 - 0;
  
      
  
  
   
  
 
 
 
 Si a l'inverse le drone se deplace autour de l'axe du "PITCH" vers l'arriére  a une vitesse de 10°/S est que votre Consigne est   égale a 0, il faut alors baissé la puissance de "mot1, mot2" est augmentez la puissance de "mot3, mot4". "EpropP =10-0" la valeur de sortie est positive +10 pour le "mot1, mot2" sa fait "0-+10 = -10" et pour "mot3, mot4" sa fait "0++10= +10.
 
 
 
    Exemple Détaillé.
 
    KPP = 1;
    KPI = 1;
    KPD = 1
 
     anglemaxP = 16 * angleP; // 32 = 16*2;
    ConsP -= anglemaxP ; // -32 = 0-32;
    EpropP = ASP - ConsP; // 42 = 10--32;
    EintP +=  EpropP; // 42 = 0 + 42;
    EdevP =  EpropP-lastEP;  42 - 0;
    EPIDP = KPP * EpropP + KPI * EintP + KPD * EdevP; // 126 = 1 * 42 + 1 * 42 + 1 * 42;
  
     mot1 = ConsG-EPIDR-EPIDP-EPIDY; //1074 = 1200 - 0 -126 - 0;
    mot2 = ConsG+EPIDR-EPIDP+EPIDY; // 1074 = 1200 + 0 -126 + 0; 
    mot3 = ConsG-EPIDR+EPIDP+EPIDY; // 1326 = 1200 - 0 +126 + 0;
    mot4 = ConsG+EPIDR+EPIDP-EPIDY; // 1326 = 1200 + 0 +126 - 0;
   
   
   
   
   
   Nous allons voir le code qui permet de configurer le deux gyroscope et accélérométre. Récupéré les données brute et les transformés en angle° et en angle°/S.
   
   
        #include <Wire.h>
   
      void communication(){
  
     Wire.beginTransmission(MPU_ADDRESS); //  on envoie l'adresse 0x68 au MPU-1 (Slave) pour lancer la transmission
     Wire.write(0x6B);// on ecrit un octet qu'on place en attente pour communiquer avec le registre PWR_MGMT_1
     Wire.write(0x00);// on ecrit un octet qu'on place en attente pour configurer la clock 8Mhz et l'alimentation
     Wire.endTransmission(); // on evoie les octets mis en attente et on termine le transmission
  
     
      Wire.beginTransmission(MPU_ADDRESS); // on envoie l'adresse 0x68 au MPU-1 (Slave) pour lancer la transmission 
      Wire.write(0x1B);// ..................... pour communiquer avec le registre GYRO_CONFIG  
      Wire.write(0x08);//........... on configure le plage de mesure du gyroscope 0°/S a ±500°/s
      Wire.endTransmission(); // on evoie les octets mis en attente et on termine le transmission 
  
      
     Wire.beginTransmission(MPU_ADDRESS); // on envoie l'adresse 0x68 au MPU-1 (Slave) pour lancer la transmission  
     Wire.write(0x1C); // ..................... pour communiquer avec le registre ACCEL_CONFIG  
     Wire.write(0x10); //...........    on configure le plage de mesure de l'accélérométre j'usqua  ±8g
     Wire.endTransmission(); //on evoie les octets mis en attente et on termine le transmission   
  
     Wire.beginTransmission(MPU_ADDRESS); //  on envoie l'adresse 0x68 au MPU-1 (Slave) pour lancer la transmission
     Wire.write(0x1A); // ..................... pour communiquer avec le registre CONFIG  
     Wire.write(0x03); //  ................pour activer un filtre passe bas ~43Hz
     Wire.endTransmission(); //on evoie les octets mis en attente et on termine le transmission 
      }
     
     
     
 On suit la meme procedure pour MPU-2. Si vous voulez changer les plage de mesure des Gyros vous avez le choix "250°/S, 500°/S, 1000°/S, 2000°/S" et pour l'accélérométre "+2g, +4g, +8g, +16g".
 
     Pour configurer le Gyro.
 
       0x00 = 250°/S      SSF_GYRO    131
       0x08 = 500°/S      SSF_GYRO    65.5
       0x10 = 1000°/S     SSF_GYRO    32.8
       0x18 = 2000°/S     SSF_GYRO    16.4
       
     Pour configure l'Accel.
       
        0x00 = +2g
        0x08 = +4g
        0x10 = +8g
        0x18 = +16g
        
        
        
   La prochaine partie de code nous permet de récupéré les données brutes des trois axes du gyroscope  de l'accélérométre et la température.
        
        
        
    Wire.beginTransmission(MPU_ADDRESS); // on envoie l'adresse 0x68 au MPU-1 (Slave) pour lancer la transmission  
    Wire.write(0x3B); // on ecrit un octet qu'on place en attente pour communiquer avec le registre ACCEL_XOUT_H
    Wire.endTransmission(); // on envoie l'octet mis en attente et on termine le transmission  
    Wire.requestFrom(MPU_ADDRESS, 14); // On demande les 14 octets  en partan de ACCEL_XOUT_H    

     
    while (Wire.available() < 14); // tan que les 14 octets ne sont pas recu on attend.

    Rollacc  = Wire.read() << 8 | Wire.read(); // on stoke la valeur d'acceleration du "ROLL" dans la variable "Rollacc"
    Pitchacc  = Wire.read() << 8 | Wire.read(); // on stoke la valeur d'acceleration du "PITCH" dans la variable  "Pitchacc"  
    Yawacc  = Wire.read() << 8 | Wire.read(); //on stoke la valeur d'acceleration du "YAW" dans la variable "Yawacc"
    temperature = Wire.read() << 8 | Wire.read(); // on stoke la temperature dans la variable "temperature"  
    Rollgyro = Wire.read() << 8 | Wire.read(); // on stoke la valeur brute du "ROLL" dans la variable " Rollgyro"  
    Pitchgyro = Wire.read() << 8 | Wire.read(); // on stoke la valeur brute du "PITCH" dans la variable " Pitchgyro" 
    Yawgyro = Wire.read() << 8 | Wire.read(); //  on stoke la valeur brute du "YAW" dans la variable " Yawgyro" 
    
    
  La partie du code qui a du surement vous interpeller ses "Wire.read() << 8 | Wire.read()".Que fait cette ligne de code ?
  Elle appelle un octet le decale de 8 bits sur la gauche puis appelle un nouvell octet quel va comparer au premier avec le comparateur binaire "ou". La valeur finale et écrite sur deux octets, je vais vous montrer un exemple ci-dessous.
  
  
      ACCEL_XOUT_H = 11000000  // premier octet appellé
      ACCEL_XOUT_L = 00010000  // Deuxiéme octet appellé
         
                 N° 7  6  5  4  3  2  1  0
                    1  1  0  0  0  0  0  0
                    
                           <<8
                   
                N° 15  14 13 12 11 10 9  8  
                    1  1  0  0  0  0  0  0  
                             
                        | Wire.read();        = 1101000000010000
                   
                N° 7  6  5  4  3  2  1  0
                   0  0  0  1  0  0  0  0
                   
                   
Le Gyro meme au repos est trés sensible au vibration "bruit" ce qui a pour effet de faire dérivée notre mesure pour éviter cela  a chaque fois que vous allumerez votre drone on va faire une moyenne du bruit pour chaque axe puis on le soustraira a la valeur brute.



      void Emoyen(){
    int max_samples = 2000;
    for (int i = 0; i < max_samples; i++) { // moyenne n = 2000 on boucle 2000 fois
    lectureMPU(); // on appelle les valeurs brutes 
     
    // on incrémentes les valeurs brutes pour chaque axe 2000 fois
    Eroll += Rollgyro; 
    Epitch += Pitchgyro;
    Eyaw += Yawgyro;
    PORTD |= B11110000; // on mes nos moteur a 0
    delayMicroseconds(1000);
    PORTD &= B00001111;
    
    delay(3);
    } // 0n divise par l'effectif 2000 pour avoir la moyenne des variations au repos
      Eroll /= max_samples; 
    Epitch /= max_samples;
    Eyaw /= max_samples;

    }
    
    
 Aprés avoir fait la moyenne des variations. On va voir la partie qui va nous permettre de transformer les valeurs brutes du gyroscope en angle.
 
 
      void ANgyro() {
     // on soustrai a chaque boucle la moyenne des variations au valeurs brutes
     Rollgyro -= Eroll;
     Pitchgyro -= Epitch;
     Yawgyro -= Eyaw;
 
     

    // on calcul l'angle par integration
    angleRO += (Rollgyro / (FREQ * SSF_GYRO));
    anglePO += (-Pitchgyro / (FREQ * SSF_GYRO)); 
     }
     
     
  Pour calculer l'angle on intégre la rotation angulaire toute les 4ms vu que notre programme fonctionnent a 250 Hz. Notre valeur brute divisée par la valeur inscrite sur la datasheet en fonction de la plage de mesure que l'on a configurée nous donne la vitesse de déplacement °/S. Je vais vous donner des exemples si votre plage de mesure est de 500 °/S la valeur donner par la datashett ces 65.5 si l'on fait "500 * 65.5 = 32750" ce qui veut dire que la valeur brute maximale qu'on recevra sera 32750 quand le drone se déplace a 500°/S "32750 /65.5 = 500 °/S" nous savon que notre programme boucle toute les 4 ms si nous recevont 32750 ca veut dire que notre drone se deplace de 500 degrés en une seconde mes vue que nous savons qu'il c'est écoulé 4ms qui représente 1/250 de seconde on fait "500/250 = 2" se qui nous donne de combien de degrés ses déplacer le drone "2°" et a chaque boucle on incrémente l'angle parcourue pour avoir notre positio en degrés.
  
  Si vous avez choisi une autre plage de mesure changer la valeur de la variable "SSF_GYRO" plus votre plage de mesure est grande moins le Gyro est précis.
  
    250 °/S   Precision: 1/131 = 0.007°/S
    500 °/S   Precision: 1/65.5 = 0.015°/S
    1000 °/S   Precision: 1/32.8 = 0.03°/S
    2000 °/S   Precision: 1/16.4 = 0.06°/S
    
    
    
    
La suite du code dans la fonction ANgyro() va nous permettre de transferer l'angle du pitch vers le roll et vis versa en fonction du yaw. Imaginez votre drone penchez vers l'arriére si vous faites tournez le drone autour de l'axe du "YAW" les valeurs de l'axe du Roll et du PITCH ne changerez pas car elle ne suibissent pas d'acceleration.
         
    void ANgyro() {
    anglePO += angleRO * sin(Yawgyro * (PI / (FREQ * SSF_GYRO * 180))); // transfer du Roll sur le PITCH sinus(radians)
  
    angleRO -= anglePO * sin(Yawgyro * (PI / (FREQ * SSF_GYRO * 180))); // // transfer du PITCH sur le ROLL sinus(radians)
    }
    // sin(-90) = -1 , sin(90)
    
    
Aprés avoir calculer les angles d'inclinaison avec le gyroscope nous allons calculer les angles avec l'accélérométre.


      void ANacc(){
                                                 
      //  Norme du vecteur acceleration ||X,Y,Z|| = √(X² + Y² + Z²): https://www.youtube.com/watch?v=tTaP48b4_5w
      acc_total_vector = sqrt(pow(Rollacc, 2) + pow(Pitchacc, 2) + pow(Yawacc, 2));
      
      if (abs(Rollacc) < acc_total_vector) {// on s'assure que la valeur reste entre -1 et 1 pour la fonction asin
      RollaccA = asin((float) Pitchacc/ acc_total_vector) * (180 / PI);// on calcule l'angle en radians grace a la fonction asin                 
    }                                                                   puis on la covertie en degrés "180/3.14 = 1rad/57.32°

    if (abs(Pitchacc) < acc_total_vector) { // on s'assure que la valeur reste entre -1 et 1 pour la fonction asin
    PitchaccA = asin((float)Rollacc/ acc_total_vector) * (180 / PI);// on calcule l'angle en radians grace a la fonction asin                 
    }                                                                 puis on la covertie en degrés "180/3.14 = 1rad/57.32°
    
    }
    
    // arcsin prend le sinus de l'angle (Pitchacc(coté opposé)/ acc_total_vector(hypothénuse)) est renvoie l'angle.
       Regardez ce pdf DGyro.pdf
    
    
    
   
   Maintenant que nous avons les angles du Gyro et de l'accélérométre nous allons fusionner les deux mesures. Le Gyro a pour avantage de ne pas étre sensible au vibration mes la mesure dérive au contraire l'accélérométre ne dérive pas mes est trés sensible au vibration donc les deux mesures se compense et en les fusionnant on aura de meilleur résultat l'angle ne dérivera pas dans le temps.
   
   Le Gyro dérive car nous prenons une valeur toute les ~4ms et nous considérons que la vitesse angulaire est la méme pendant les 4ms alors quand réalité ses faut. L'accélérométre ne dérive pas car il mesure l'angle en utilisant l'apesanteur terrestre 9.81 m-s. D'ailleurs nous verrons juste aprés dans la partie ou l'on fusionne les deux mesures que plus votre programme a une frequence élevé moins nous utilisons la mesure de l'accelérométre

  
  
      
       

 
 
 






          
                 
    
    
   
   
  
  
 
 
 
 
 
 
 
 

 
 
 
 
 









https://www.youtube.com/watch?v=bCEiOnuODac

Frame impression 3D .

Controleur de vol P.I.D: arduino Uno ou arduino Mega. 
https://www.youtube.com/watch?v=yRw2mC_6A00


 
 
  
 <img src="https://user-images.githubusercontent.com/52819943/78615340-866ab880-7871-11ea-9ce7-7f5a4f877526.png" width="200" height="125">
 
  
  <img src="https://user-images.githubusercontent.com/52819943/78615820-c67e6b00-7872-11ea-9dfd-4ab4ac3a28b6.png" width="200" height="125">
  
   
   <img src="https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/%20MPU6050SHEMA.png" width="400" height="400">
 

 
 

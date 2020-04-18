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
  
  Notre programme recoit les commandes ordonné par notre radiocommande qui lui donne un angle a atteindre (Consigne) est les donnés du gyroscopes qui lui donne sa position actuelle est a la vitesse a laquelle le drone se déplace autour de ses trois axes.
  
  
  -lecture des données recus par le recepteur
  
  
  Pour calculer l'angle a atteindre il faut d'abord lire la largeur d'impulsion de chaque CH rappeller vous on en a parler dans la partie " Radiocommande & recepteur" pour lire la largeur on va utiliser les interruptions en mode "Changes" ce qui veut dire quells activent l'orsque l'état de la CH passent de l'etat haut(5v) a bas(0v) ou de bas a haut.  Quand une interruption s'activent elle est prioritaire sur notre programme et lance une routine execution qui va faire les calculs pour connaitre la largeur d'impulsion. Une fois que le code de la routine est executer le programme reprend ou il ces arrété, si le code de la routine est trop volumineux votre programme ne fonctionnera pas car elle sera réappeller alors que l'execution du code n'est toujour pas finit.
  

Pour pouvoir les utiliser il faut declarer les interruptions le code suivant indique a l'arduino uno que les pins digital 8,9,10,11  vons etre uitliser comme interruptions en modes "Changes".  
   
     //N°bit = 76543210   //table de vérité "ou" = "1&0=1" "0&0=0" "1&1=1 
   
   
    //PCIRC = 00000000;
   
   
    //PCMSK0 = 00000000;
   
   
    PCICR  |= (1 << PCIE0); //PCIRC = 00000001; on utilise le comparateur "ou" est on decale de 0 la valeur 1 dans PCICR  
   
   
    PCMSK0 |= (1 << PCINT0); //PCMSK0 = 00000001; ................................................................PCMSK0 D8
   
   
    PCMSK0 |= (1 << PCINT1); //PCMSK0 = 00000011; on utilise le comparateur "ou" est on decale de 1 la valeur 1 dans PCMSK0 D9
   
   
    PCMSK0 |= (1 << PCINT2); //PCMSK0 = 00000111; on utilise le comparateur "ou" est on decale de 2 la valeur 1 dans PCMSK0 D10
   
   
    PCMSK0 |= (1 << PCINT3); //PCMSK0 = 00001111; on utilise le comparateur "ou" est on decale de 3 la valeur 1 dans PCMSK0 D11
   

Pour bien comprendre le fonctionnement il faut imaginer un octet superposer a un autre octet ces pour sa que le "ou" est un comparateur de bit je vais donner des exemples
   
   
   
   
   
   
    PCMSK0 = 00000000; // le registre PCMSK0 se représente sur un octet 
   
   
    l'orsque nous faisons |= (1 << PCINT0) il se passe la chose suivante.
    
    
    PCMSK0 = 00000000;
                 
                 
                 |=          PCMSK0 =  00000001;
            
            
            00000001;
     
    l'orsque nous faisons |= (1 << PCINT1) il se passe la chose suivante.
             
    
    PCMSK0 = 00000001;
                 
                 
                 |=          PCMSK0 =  00000011
             
             
             00000010;
                 
    
    
   
   
  
  
 
 
 
 
 
 
 
 

 
 
 
 
 









https://www.youtube.com/watch?v=bCEiOnuODac

Frame impression 3D .

Controleur de vol P.I.D: arduino Uno ou arduino Mega. 
https://www.youtube.com/watch?v=yRw2mC_6A00


 
 
  
 <img src="https://user-images.githubusercontent.com/52819943/78615340-866ab880-7871-11ea-9ce7-7f5a4f877526.png" width="200" height="125">
 
  
  <img src="https://user-images.githubusercontent.com/52819943/78615820-c67e6b00-7872-11ea-9dfd-4ab4ac3a28b6.png" width="200" height="125">
  
   
   <img src="https://raw.githubusercontent.com/ul34/Drone-imprimante3d/master/%20MPU6050SHEMA.png" width="400" height="400">
 

 
 

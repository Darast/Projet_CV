Équipe Ground :
	Clément Sanquer
	Damien Sureau
	Sébastien Mick


Préparation : 
	Le dossier data/ doit contenir la hierarchie suivante :
		data/
			verites/
				log1/ 
				log2/ 
				log3/ 
				log4/
	Le chemin du dossier contenant les images à traiter est à passer en paramètre au script de test, il doit contenir la hierarchie suivante:
		log1/ 
		log2/ 
		log3/ 
		log4/
	Les noms des images de ne doivent pas avoir été changés.

Compilation : 
	Compiler en premier lieu les sources dans src/ avec la commande:
		qmake-qt4 terrain_efficace.pro (pour la version la plus efficace)
 		qmake-qt4 terrain_rapide.pro (pour la version la plus rapide)
 	Puis make
 	L'executable "terrain_efficace" et/ou l'executalbe "terrain_rapide" se trouve(nt) dans le dossier build/ et est/sont prêt à être utilisé(s).
	
	Pour lancer les différents programmes, il faut utiliser la commande suivante :
		./terrain_VERSION <chemin vers l'image source> <chemin vers l'image de sortie>

	Par exemple, pour utiliser le programme "efficace" avec l'image source "001-rgb.png" du log1 et enregitre l'image obtenue sous le nom "out.png":
		./terrain_efficace ../%Chemin vers les images%/log1/001-rgb.png out.png

 	Pour executer les tests sur les vérités terrain, se placer dans le dossier tst/ et executer la commande : 
 		qmake-qt4 difference.pro
 	Puis make
 	L'executable se trouve dans le dossier build/

Vérités terrain :
	log1 :
		003
		010
		105
		120
		151
		163
	log2 :
		005
		158
		175
	log3 :
		005
		143
	log4 :
		021
		046
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
 	L'executable "terrain" se trouve dans le dossier build/ et est prêt à être utilisé.

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
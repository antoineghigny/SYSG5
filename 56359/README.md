# SYSG5 : Failles de sécurité LINUX

# Où générer le pdf du rapport avec la commande pdflatex

```
56359\Rapport
```
Exécuter le script : script.sh
- pdflatex : Permet de compiler et générer un document PDF à partir du fichier TEX
- bibtex : Permet de gérer les rérérences bibliographiques pour les inclure dans le fichier LATEX
- pdflatex Permet d'inclure les références bibliographiques dans le rapport, mais également d'ajouter la table des matières après avoir lu une première fois le document tex en ayant compilé une première fois avant.
- pdflatex : Une fois que le rapport a été compilé avec les références bibliographiques, intégrer celles-ci dans les citations au cours du document

# Comment setup l'environnement de dévelopement ?

Toutes les explications nécéssaires sont disponibles dans le rapport pdf.

- Il y a notemment des explications sur la manière dont créer un stick USB bootable contenant l'image disque de Debian 10.7.0
- La manière dont j'ai configuré mes partitions sur les pc de l'ESI
- La configuration du réseau 
- L'installation des packets requis.

# Comment compiler mes codes & Exécuter ?

```
56359\Code\SetupEnvironnement\
```
- chmod u+x report.sh
- ./report.sh

Le script script.sh Permet d'inclure les sources complètes de debian dans le fichier /apt/etc/sources.list, de télécharger la liste des pacjets de debian. Mais également d'installer des packets nécéssaires au bon fonctionnement du programme, tel que git, make ou encore gcc.

```
56359\Code\PwnKit\
```
- Dans ce dossier, un script Demo permet de compiler le programme via un Makefile, mais également d'exécuter le programme en C. Si la faille n'est pas exploitable sur votre système, le programme vous le fera comprendre. 

- Pour la modification du GRUB et permettre de modifier le mot de passe root du système sans le connaître, une automatisation ne peut pas être effectuée, les explications sont notemment disponibles sur le rapport pdf.
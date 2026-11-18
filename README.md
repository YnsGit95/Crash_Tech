# 📘 Projet-Crash-Tech

Synthèse et analyse des statistiques liées aux accidents de la route survenus en France entre 2005 et 2024.  
**CY Tech – pré-ING2 – 2026/2027**

---

## 🎯 Description du projet

Ce projet a pour objectif de réaliser un outil d’analyse de données des statistiques liées aux accidents de la route survenus en France entre 2005 et 2024 à partir d’un fichier CSV volumineux contenant les détails (gravités, victimes, véhicules impliqués, etc.) de **1 286 097 accidents** réels récupérés auprès de l’Observatoire National de la Sécurité Routière (ONISR).

L’application est composée :
- d’un programme en langage C modulaire chargé d’effectuer les calculs intensifs via des structures de données adaptées (tableau statique, listes chaînées et arbres AVL) ;
- d’un `Makefile` permettant la compilation automatique et le nettoyage des fichiers générés.

---

## 📊 Format des données fournies

Le fichier CSV fourni utilise le point-virgule (`;`) comme séparateur de colonnes. Chaque ligne correspond aux caractéristiques d'une victime impliquée dans un accident :

Le fichier CSV fourni utilise le point-virgule (;) comme séparateur de colonnes. Chaque ligne correspond aux caractéristiques d'une victime impliquée dans un accident :

```year``` : l'année de l'accident.

```collision_id``` : numéro d'identification de l'accident.

```vehicle_id``` : identifiant du véhicule impliqué.

```location``` : emplacement de la victime dans le véhicule (ex. 1 : conducteur, 2 : passager avant, 10 : piéton, etc.).

```user_type``` : type d'usager (1 : conducteur, 2 : passager, 3 : piéton).

```severity``` : gravité de l'accident pour la victime (1 : indemne, 2 : tué, 3 : blessé grave, 4 : blessé léger).

```gender``` : genre de la victime (1 : masculin, 2 : féminin, autre si non relevé).

```birth_year``` : année de naissance de la victime.

```purpose``` : type de trajet (-1/0 : non renseigné, 1 : domicile-travail, 2 : domicile-école, 3 : courses, 4 : déplacement professionnel, 5 : loisirs, 6+ : autres).

---

## ⚙️ Fonctionnalités et Traitements

Lors de l'exécution, l'utilisateur doit obligatoirement indiquer le type de traitement souhaité ainsi que le fichier de données en arguments :

### 1. Statistiques par année (`YEAR_DATA` - Tableau statique)
- **Commande :**
  ```bash
  ./crashTech YEAR_DATA data.csv
  ```
- Fournit pour chaque année entre 2005 et 2024 le nombre total d'accidents ainsi que la répartition par type de sévérité (morts, blessés légers, blessés graves, indemnes).
- Consultation interactive via un menu permettant d'interroger plusieurs années successivement. Le stockage repose sur un tableau statique de 20 cases.

### 2. Statistiques par âge (`AGE_DATA` - Liste chaînée)
- **Commande :**
  ```bash
  ./crashTech AGE_DATA data.csv
  ```
- Génère une pyramide des âges affichant les pourcentages selon le type d'usager (piéton, passager, conducteur) et le genre.
- Possibilité d'appliquer des filtres ciblés (par exemple : répartition par âge des femmes piétonnes). Le stockage s'appuie sur une liste chaînée dynamique où chaque chaînon représente un âge.

### 3. Recherche d'un accident (`CRASH_DATA` - AVL)
- **Commande :**
  ```bash
  ./crashTech CRASH_DATA data.csv
  ```
- Permet de rechercher un accident précis à partir de son année et de son `collision_id`.
- Affiche un récapitulatif détaillé : la liste des véhicules impliqués avec leurs motifs de trajet (`purpose`), ainsi que la liste des victimes associées à chaque véhicule (âge, genre et gravité).
- Le stockage utilise un **arbre AVL** trié par une clé combinée (`year + collision_id`, ex. `200500000001`), où chaque nœud contient une liste chaînée de véhicules pointant chacun vers une liste chaînée de victimes.

---

## 🛠️ Compilation et Exécution

1. **Cloner le dépôt :**
   ```bash
   git clone https://github.com/YnsGit95/Crash_Tech
   cd Crash_Tech
   ```
2. **Placer le fichier de données** (`data.csv`) à la racine du dossier du projet.
3. **Compiler le programme :**
   ```bash
   make
   ```
4. **Nettoyer les fichiers objets et l'exécutable :**
   ```bash
   make clean
   ```

---

## ⚠️ Gestion des erreurs et Robustesse

- **Validation des arguments :** En cas de commande incorrecte, incomplète ou de fichier introuvable, le programme affiche un message d'erreur explicite et s'arrête proprement.
- **Gestion de la mémoire :** Optimisation de l'empreinte mémoire des structures et libération systématique de toutes les allocations dynamiques avant la fin d'exécution.
- **Architecture modulaire :** Code découpé en plusieurs fichiers `.h` et `.c`, indenté et commenté, garanti sans fuite mémoire ni erreur de segmentation (`segmentation fault`).

---

## 👥 Auteurs

- Mohamed-Amir **NOUMA**
- Yanis **ABTTA**
- Lucien **LEHEUDRE--EPSTEIN**

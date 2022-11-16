# Introducere In Robotica

<details>
  <summary><h3>Tema 1</h3></summary>

<br>
Proiectul de la tema 1 este un LED rgb ale cărui culori sunt controlate individual de 3 potențiometre.
Input-ul potențiometrelor este preluat de placa arduino, transformat intr-o valoare cuprinsa între 0 și 256 (range-ul de intensitate al LED-ului) și transmis către LED

Source code: https://github.com/WildCola/Robotica/blob/main/PotentiometruRGB/PotentiometruRGB.ino

Link către video: https://youtu.be/Gh3H4ZXLa54

![image](https://user-images.githubusercontent.com/79272874/199030891-c6258d9e-ff5f-4064-b904-d6325a5d90b4.png)
</details>

<details>
  <summary><h3>Tema 2</h3></summary>

<br>
Tema 2 a cerut construirea unui sistem de semafoare pentru masini si pietoni. Acesta are 4 stari:
<ol>
<li> Verde pentru masini, rosu pentru pietoni, fara sunet, se schimba doar dupa apasarea butonului
<li> Galben pentru masini, rosu pentru pietoni, fara sunet, incepe la 8 secunde dupa apasarea butonului si dureaza 3 secunde
<li> Rosu pentru masini, verde pentru pietoni, bazait la un interval constant, dureaza 8 secunde
<li> Rosu pentru masini, clipeste verde pentru pietoni, bazait la interval mai rapid, dureaza 4 secunde, apoi revine in starea 1
</ol>

Proiectul a fost realizat prin folosirea unui buton, care porneste un contor de timp in momentul apasarii cu ajutorul unei functii interrupt, apoi la momentele cheie de timp descrise mai sus, placa arduino trimete semnale LED-urilor si buzzer-ului pentru a le duce in starea corespunzatoare intervalului de timp.
  
Source code: https://github.com/WildCola/Robotica/blob/main/crosswalk/crosswalk.ino

Link către video: https://www.youtube.com/shorts/QCxIFdsp5OE

![image](https://user-images.githubusercontent.com/79272874/199129636-cfa44ddb-e8ab-4500-9569-8cc49e441189.png)
  
</details>

<details>
  <summary><h3>Tema 3</h3></summary>

<br>
Tema 3 - Desenezi pe un seven segment display cu ajutorul unui joystick. Are 2 stadii:
<ol>
<li> Poti folosi joystick-ul pentru a naviga segmentele display-ului. Segmentul selectat se aprinde si stinge intermitent. O apasare scurta a butonului de pe joystick trece in stadiul 2. O apasare lunga reseteaza display-ul si te muta pe DP.
<li> Segmentul selectat ramane in starea (stins sau aprins) in care se afla la apasarea butonului. Axa X a joystick-ului stinge sau aprinde segmentul. Apasarea butonului salveaza starea curenta a segmentului si trece inapoi in stadiul 1.
</ol>

Pentru navigarea display-ului am folosit o matrice de vecini (fiecare segment are 4 vecini, cate unul pentru fiecare directie a joystick-ului).
Pentru a diferentia intre apasarea scurta si cea lunga a butonului am folosit un cronomentru care porneste la apasarea butonului. Daca butonul este ridicat in mai putin de o secunde programul inregistreaza o apasare scurta si trece in stadiul 2, daca butonul este apasat pentru mai mult de o secunda display-ul va fi resetat.

Source code: https://github.com/WildCola/Robotica/blob/main/joystick/joystick.ino

Link catre video: https://youtube.com/shorts/hWmcDOIERwg

![image](https://user-images.githubusercontent.com/79272874/200663000-821bd8a3-1da8-457c-b45a-4801c569c4ea.png)
  
</details>

<details>
  <summary><h3>Tema 4</h3></summary>
  
<br>
Tema 4 - Joystick cu care reglezi cifrele unui 4 Digit Display. Programul are 2 stari:
<ol>
<li> Folosesti axa Y a joystick-ului pentru a naviga cele patru pozitii ale display-ului, cifra selectata este indicata prin clipirea segmentului DP. O apasare scurta de buton de duce in starea 2, o apasare lunga reseteaza toate cifrele la 0 si te muta pe pozitia cea mai din dreapta.
<li> Folosesti axa X pentru a creste sau a scadea cifra de pe segmentul selectat inaintea intrarii in starea 2. Apasarea butonului salveaza cifra modificata si te duce inapoi in starea 1.
</ol>

Pentru navigarea pozitilor display-ului am folosit o variabila ce retine display-ul curent selectat, aceasta variabila creste sau scade cu miscarea axei Y a joystick-ului. Pentru schimbarea cifrei am folosit un array de 4 elemente, in care maream sau scadeam valoarea elementului corespunzator pozitiei selectate pe display cu miscarea axei X a joystick-ului. 
Pentru a diferentia intre apasarea scurta si cea lunga a butonului am folosit un cronomentru care porneste la apasarea butonului. Daca butonul este ridicat in mai putin de o secunde programul inregistreaza o apasare scurta si trece in stadiul 2, daca butonul este apasat pentru mai mult de o secunda display-ul va fi resetat.

Source code: https://github.com/WildCola/Robotica/blob/main/4digit/4digit.ino

Link catre video: https://youtube.com/shorts/pcH-yyNJsJI

![image](https://user-images.githubusercontent.com/79272874/202056975-73ac43b4-55e4-4e66-a824-88118d336c76.png)
  
</details>



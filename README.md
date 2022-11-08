# Introducere In Robotica

<details>
<summary>Tema 1</summary>

<br>
Proiectul de la tema 1 este un LED rgb ale cărui culori sunt controlate individual de 3 potențiometre.
Input-ul potențiometrelor este preluat de placa arduino, transformat intr-o valoare cuprinsa între 0 și 256 (range-ul de intensitate al LED-ului) și transmis către LED

Source code: https://github.com/WildCola/Robotica/blob/main/PotentiometruRGB/PotentiometruRGB.ino

Link către video: https://youtu.be/Gh3H4ZXLa54

![image](https://user-images.githubusercontent.com/79272874/199030891-c6258d9e-ff5f-4064-b904-d6325a5d90b4.png)
</details>

<details>
  <summary><h1>Tema 2</h2></summary>

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

<br>
Tema 3 - Desenezi pe un seven segment display cu ajutorul unui joystick. Are 2 stadii:
<ol>
<li> Poti folosi joystick-ul pentru a naviga segmentele display-ului. Segmentul selectat se aprinde si stinge intermitent. O apasare scurta a butonului de pe joystick trece in stadiul 2. O apasare lunga reseteaza display-ul si te muta pe DP.
<li> Segmentul selectat ramane in starea (stins sau aprins) in care se afla la apasarea butonului. Axa X a joystick-ului stinge sau aprinde segmentul. Apasarea butonului salveaza starea curenta a segmentului si trece inapoi in stadiul 1.

Pentru navigarea display-ului am folosit o matrice de vecini (fiecare segment are 4 vecini, cate unul pentru fiecare directie a joystick-ului).
Pentru a diferentia intre apasarea scurta si cea lunga a butonului am folosit un cronomentru care porneste la apasarea butonului. Daca butonul este ridicat in mai putin de o secunde programul inregistreaza o apasare scurta si trece in stadiul 2, daca butonul este apasat pentru mai mult de o secunda display-ul va fi resetat.

Source code: https://github.com/WildCola/Robotica/blob/main/joystick/joystick.ino

Link catre video: https://youtube.com/shorts/hWmcDOIERwg

![image](https://user-images.githubusercontent.com/79272874/200663000-821bd8a3-1da8-457c-b45a-4801c569c4ea.png)
  
</details>



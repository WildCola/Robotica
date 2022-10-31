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
<summary>Tema 2</summary>

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


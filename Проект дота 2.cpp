#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

char answ;
class Team;
class The_International;
class Support;
class Player;
int stats;
class DCP;

string heroes_list[40] = {"Lina", "Monkey King", "Phantom Assasin", "Pudge", "Sniper", "Windranger", "Axe", "Bloodseeker", 
"Crystal Maiden", "Bristleback", "Bounty Hunter", "Bane", "Broodmother", "Anti-Mage", "Abaddon", "Drow Ranger", "Invoker", 
"Legion Commander", "Luna", "Nature`s Prophet", "Witch Doctor", "Chen", "Pepuga", "Ursa", "Batrider", "Razor", "Lone Druid", 
"Slark", "Hoodwink", "Troll Warlord", "Phantom Lancer", "Meepo", "Terrorblade", "Naga Siren", "Weaver", "Viper", "Riki", 
"Lifestealer", "Sven", "Io"};

//функція рандому , яку я буду потім використовувати для вибору героя
int random(int min, int max) {
    int num = min + rand() % (max - min + 1);
    return num;
}

class Player {
    public:
        string name;
        string role;
        string nickname;
        string hero;
};
// клас DCP сезон в який входять 2 методи , параметрами яких є команда
class DPC {
    public:
        void major(Team& team);
        void bootcamp(Team& team);
};
// клас підтримка , яка характеризується типом кухні , психологом та видом спортивних тренувань
class Support {
    string dinner_set;
    string sport_type;
    string psychologist;
    public:
        void physical();
        void dinner();
        void sport();
        void psychology();
};
// метод фізичної підтримки , сюди відноситься харчування + спорт
void Support::physical(){
    dinner();
    sport();
}
// обираємо кухню
void Support::dinner(){
    int answ;
    cout << "Choose cuisine:\n1. Japanese\n2. Korean\n3. Ukrainian\n4. American\n5. Italian\n";
    cin >> answ;
    switch(answ){
        case 1: {
            dinner_set = "Japanese";
            break; }
        case 2: {
            dinner_set = "Korean";
            break; }
        case 3: {
            dinner_set = "Ukrainian";
            break; }
        case 4: {
            dinner_set = "American";
            break; }
        case 5: {
            dinner_set = "Italian";
            break; }
        default: dinner();
    }
}
//обираємо важкість спортивних тренувань
void Support::sport(){
    int answ;
    cout << "Choose sport type:\n1. Easy\n2. Medium\n3. Hard\n";
    cin >> answ;
    switch(answ){
        case 1: {
            sport_type = "Easy";
            break; }
        case 2: {
            sport_type = "Medium";
            break; }
        case 3: {
            sport_type = "Hard";
            break; }
        default: sport();
    }
}
//обираємо психолога
void Support::psychology(){
    int answ;
    cout << "Choose psychologist:\n1. Yo Asakura\n2. Anna Kyoyama\n3. Ren Tao\n";
    cin >> answ;
    switch(answ){
        case 1: {
            psychologist = "Yo Asakura";
            break; }
        case 2: {
            psychologist = "Anna Kyoyama";
            break; }
        case 3: {
            psychologist = "Ren Tao";
            break; }
        default: psychology();
    }
}

class The_International {
    public:
        void qualification(Team& team, int n);
        void TI(Team& team);
};

class Team {
    bool is_ready = false;
    string name;
    string roles[5] = {"Carry", "Mid", "Hard", "Support", "Hard-Support"};

    public:
        bool is_full = false;
    	bool major_participation = false;
        Support support;
        Player team[5];
        int exp = 0;// дана змінна використовуватиметься для аналітики своєї та суперників , вона змінюється від результатів матчу
        void sign_members(int i);
        void choose_role();
        void choose_hero(vector<int> exclude);
        void choose_name();
};

class Analytics {
    public:
        void team_analytics(Team& team);
        void competitor_analytics(Team& team);
};
// тут ми виводимо свою статистику
void Analytics::team_analytics(Team& team) {
    cout << "Your stats: " << team.exp << endl;
}
// тут ми виводимо стастистику суперника
void Analytics::competitor_analytics(Team& team) {
    if (team.major_participation) {// якшо брали участь у major
        stats = random(10, 100);// рейтинг суперників рандомно вибирається
        cout << "Your competitor stats: " << stats << endl;
        if (stats > team.exp) { //порівнюємо свою статистику з значеннями суперника і виводимо результат
            cout << "The other team is strong. You need more preparation\n";
        } else { 
            cout << "You seem to be stronger\n";
        }
    } else { // якшо не брали участь
        cout << "You haven`t visited major\n";
    }
}
//метод тренувальний табір
void DPC::bootcamp(Team& team){
    vector<int> exclude;
    int answ;

    cout << "Starting a bootcamp\n";
    cout << "How many matches do you want to have?\n"; 
    cin >> answ;
    for (int i = 0; i < answ; i++){// створюємо приклад проходження турніру
        int v = rand()% 100;// рандомна змінна від якої залежить результат матчу
        team.choose_hero(exclude);//герої вибираються з вектору exclude
        if (v%13 == 0) {//13 із-за того що чисел , які діляться на 13 не так і багато а нічия - рідка подія
            cout << "It`s a draw: you have run of time\n";
            team.exp += 5;
        } else if (v%2 == 0) {//якщо число парне 
            cout << "Victory!\n";
            team.exp += 10;
        } else {
            cout << "You were defeated\n";
            team.exp += 5;
        }
    }  
}

void DPC::major(Team& team){
    int answ;
    bool state;
    vector<int> exclude;

    cout << "Starting a major\n";                                                                                                                                                                                                         
    for (int i = 0; i < 3; i++){
        // ось тут ми забираємо кожного разу 7 героїв 
        for(int k = 0; k < 7; k++){//рандомний бан
            int v = random(0, 39);
            exclude.push_back(v);
        }
        // вивід для моніторингу і демонстрації роботи 
        cout << "Excluded heroes are: ";
        for(int k = 0; k < exclude.size(); k++){
            cout << heroes_list[exclude[k]] << "; ";
        }
        cout << endl;
        team.choose_hero(exclude);
        int v = rand()% 100;
        if (v%13 == 0) {
            cout << "It`s a draw: you have run of time\n";
            team.exp += 5;
        } else if (v%2 == 0) {
            cout << "Victory!\n";
            team.exp += 10;
        } else {
            cout << "You were defeated\n";
            team.exp += 5;
        }
    }
}

void Team::choose_name(){
    cout << "Choose name: ";
    cin >> name;
}

// тут ми вибираємо героїв , виключаючи з можливих забанених із вектору exclude
void Team::choose_hero(vector<int> exclude){
    int i = 0;
    bool is_here;
    cout << "Choosen heroes are:\n";
    choose_role();
    while (i < 5){
        int hero = random(0, 39);
        for (int k = 0; k < exclude.size(); k++){
            if (hero == exclude[k]) {// якщо значення якогось героя = значенню героя з вектору exclude , буде повторюватися , нам треба значення false
                is_here = true;
		break;
            } else is_here = false;
        }

        if (is_here == false) {// коли false вибирається герой з списку героїв 
            team[i].hero = heroes_list[hero];
            cout << "   " << team[i].nickname << " - " << team[i].role << " - " << team[i].hero << endl;
            exclude.push_back(hero);// коли вибрався , то цей герой додається в exclude
            i++;
        }
    }
}

void Team::choose_role(){
vector<int> list;
	list.push_back(6);
	bool is_here = false;
	int i = 0;
	
	int r;
	while (i< 5) {
		int r = random(0, 4);
		for (int k = 0; k < list.size(); k++){
            if (r == list[k]) {// якщо значення ролі = значенню ролі з списку використаних , буде повторюватися , нам треба значення false
                is_here = true;
                break;
            } else is_here = false;
        }

        if (is_here == false) {
            team[i].role = roles[r];
            list.push_back(r);// коли вибрався , то ця роль додається в використані
            i++;
        }
	}
}

void Team::sign_members(int i){
    cout << "Player #" << i << endl;
    cout << "Enter name: ";
    cin >> team[i].name;
    cout << "Enter nickname: ";
    cin >> team[i].nickname;
}

void The_International::qualification(Team& team, int n) {
    vector<int> exclude;
    for (int i = 0; i < n; i++){// в цьому циклі рандомно банимо героїв
        for(int k = 0; k < 7; k++){
            int v = random(0, 39);
            exclude.push_back(v);// додаємо у вектор exclude
        }
      
        cout << "Excluded heroes are:sds ";// виводимо цих героїв
        for(int k = 0; k < exclude.size(); k++){
            cout << heroes_list[exclude[k]] << "; ";
        }
        cout << endl;
        team.choose_hero(exclude);
        int v = rand()% 100;
        if (v%13 == 0) {
            cout << "It`s a draw: you have run of time\n";
            team.exp += 5;
        } else if (v%2 == 0) {
            cout << "Victory!\n";
            team.exp += 10;
        } else {
            cout << "You were defeated\n";
            team.exp += 5;
        }
    }
}

void The_International::TI(Team& team){
    int matches;
    vector<int> exclude;

    cout << "Welcome to the International!\n";
    for (int i = 0; i < 3; i++){
        for(int k = 0; k < 7; k++){
            int v = random(0, 39);
            exclude.push_back(v);
        }

        cout << "Excluded heroes are: ";
        for(int k = 0; k < exclude.size(); k++){
            cout << heroes_list[exclude[k]] << "; ";
        }
		cout << endl;
		
        if (stats > team.exp) cout << "Your team was defeated(\n";
        else cout << "You won!\n";
    }
}

class Coach {
    Analytics a_team;

    public:
        void team_sign(Team& team);
        void prepare_support(Team& team);
        
        void DCP(Team& team, DPC& dpc);
        void start_ananytics(Team& team);
        void change_player(Team& team);
        
        void TI(Team& team, The_International& TI);
};

void Coach::team_sign(Team& team){//підписання команди , повторюємо поки не буде повна
    cout << "Signing the team\n";
    for (int i = 0; i < 5; i++){
        team.sign_members(i);
    }
    team.is_full = true;
    cout << "Team is full!\n";
}

void Coach::prepare_support(Team& team){//забезпечення команди різноманітною підтримкою
    int v = rand()% 100;
    if (v % 2 == 0) {
        team.support.physical();
        team.support.psychology();
    } else {
        team.support.psychology();
        team.support.physical();
    } 
}

void Coach::DCP(Team& team, DPC& dpc){
    cout << "Do you want to visit bootcamp?\n";
    cin >> answ;
    if (answ == 'y' || answ == 'Y'){
        dpc.bootcamp(team);
    }
    
    cout << "Are you going to visit major?\n";
    cin >> answ;
    if (answ == 'y' || answ == 'Y'){
        dpc.major(team);
        team.major_participation = true;
    }
}

void Coach::start_ananytics(Team& team) {
    do {
        a_team.competitor_analytics(team);
        a_team.team_analytics(team);
        cout << "One more time?\n";
        cin >> answ;
    } while (answ == 'y' || answ == 'Y');
}

void Coach::change_player(Team& team){
    int player;

    cout << "Which player do you want to change?\n";
    cin >> player;
    cout << "Player was deleted\n";
    team.sign_members(player);
}

void Coach::TI(Team& team, The_International& TI){
    int matches;
    // перевірка на участі у турнірі major
    if (!team.major_participation) {
        cout << "You haven`t visited major, now it is a chance to\n";
        cout << "How many matches do you want to have?\n";
        cin >> matches;
        TI.qualification(team, matches);
        team.major_participation = true;
    }

    cout << "Do you need analytics?\n";
    cin >> answ;
    if (answ == 'y' || answ == 'Y'){
        start_ananytics(team);
    }

    TI.TI(team);
}

int main(){
    Team team;
    Coach coach;

    DPC dpc;
    The_International international;
	
    coach.team_sign(team);
    coach.prepare_support(team);
    coach.DCP(team, dpc);
    
    cout << "Do you need analytics?\n";
    cin >> answ;
    if (answ == 'y' || answ == 'Y'){
        coach.start_ananytics(team);
    }

    cout << "Do you want to change a team member?\n";
    cin >> answ;
    if (answ == 'y' || answ == 'Y'){
        coach.change_player(team);
    }

    coach.TI(team, international);

    return 0;
}

#ifndef MODEL_H
#define MODEL_H

#include "Workspace.h"
#include "Creator.h"

class Model {
private:
    WorkSpace* workspace;

    /**
     * @brief checkNuoviPunti   controlla se i punti passati sono già presenti in workspace
     * @param points            vettore dei punti da controllare
     * @return                  TRUE sse dentro points c'è un nuovo punto non presente in workspace
     */
    bool checkNuoviPunti(const Vettore<Punto*>& points) const;

    /**
     * @brief className enum    enum per una gestione più semplice dell'I/O
     */
    enum className { segmento =0, retta =1, poligono =2, regolare=3, ellisse=4, circonferenza=5, punto=6 };
public:
    Model();
    ~Model();

    /**
     * @brief addNewSegmento        Aggiunge un nuovo segmento al Model
     * @param A                     Primo punto
     * @param B                     Secondo punto
     * @param nome                  Nome del segmento
     * @param color                 Colore del segmento
     * @throw std::logic_error      se A == B (i punti devono essere diversi, altrimenti il segmento collassa su un punto)
     */
    void addNewSegmento(Punto* A, Punto* B, string nome= "segmento", string color= "#000000") const;

    /**
     * @brief addNewRetta           Aggiunge una nuova retta al Model
     * @param A                     Primo punto
     * @param B                     Secondo punto
     * @param nome                  Nome della retta
     * @param color                 Colore della retta
     * @throw std::logic_error      se A == B (i punti devono essere diversi, altrimenti non è possibile identificare una retta)
     */
    void addNewRetta(Punto* A, Punto* B, string nome="retta", string color= "#000000") const;

    /**
     * @brief addNewPoligono        Aggiunge un nuovo poligono al Model
     * @param punti                 Vettore con i puntatori ai punti coinvolti per il poligono
     * @param nome                  Nome del poligono
     * @param color                 Colore del poligono
     * @throw std::logic_error      se punti contiene due punti uguali
     */
    void addNewPoligono(const Vettore<Punto*>& punti, string nome="poligono", string color= "#000000") const;

    /**
     * @brief addNewRegolare        Aggiunge un nuovo regolare al Model
     * @param punti                 Coppia con i puntatori ai punti dai quali viene disegnato il regolare
     * @param numLati               Numero dei lati di cui è composto
     * @param nome                  Nome del regolare
     * @param color                 Colore del regolare
     * @throw std::logic_error      se numLati < 3 || numLati > 12
     */
    void addNewRegolare(const std::pair<Punto*, Punto*>& punti, unsigned int numLati, string nome="regolare", string color= "#000000") const;

    /**
     * @brief addNewEllisse         Aggiunge una nuova ellisse al Model
     * @param centro                Puntatore al centro
     * @param semiAsse1             misura del primo semi-asse
     * @param semiAsse2             misura del secondo semi-asse
     * @param nome                  Nome dell'ellisse
     * @param color                 Colore dell'ellisse
     * @throw std::domain_error     se semiAsse1 < 0 || semiAsse2 < 0 (non posso avere dei semi-assi negativi
     */
    void addNewEllisse(Punto* centro, double semiAsse1, double semiAsse2, string nome="ellisse", string color= "#000000") const;

    /**
     * @brief addNewCirconferenza   Aggiunge una nuova circonferenza al Model
     * @param centro                Puntatore al centro
     * @param raggio                misura del raggio
     * @param nome                  Nome della circonferenza
     * @param color                 Colore della circonferenza
     * @throw std::domain_error     se raggio <= 0
     */
    void addNewCirconferenza(Punto* centro, double raggio, string nome="circonferenza", string color= "#000000") const;

    /**
     * @brief addNewPunto           Aggiunge un nuovo punto al Model
     * @param x                     Ordinata x
     * @param y                     Ascissa y
     * @param nome                  Nome del punto
     * @param color                 Colore del punto
     */
    void addNewPunto(double x, double y, string nome="P", string color= "#000000") const;

    /**
     * @brief removeDisegno         Rimuove un Disegno in posizione index-esima dal Model
     * @param index                 index del Disegno
     * @throw std::out_of_range     se index non è tra i disegni presenti
     */
    void removeDisegno(unsigned int index) const;

    /**
     * @brief refresh               Ridisegna tutti i disegni sul piano cartesiano
     */
    void refresh() const;

    /**
     * @brief cancellaTutto         Elimina tutti i disegni dal workspace
     */
    void cancellaTutto() const;

    /**
     * @brief getInfoDisegnabile    Get delle info dell'ultimo disegno inserito
     * @return                      unordered_map con le info
     */
    std::unordered_map<string, string> getInfoDisegnabile() const;

    /**
     * @brief getTutteInfo          Get di tutte le info dei disegni presenti in workspace
     * @return                      vettore di unordered_map contenenti le info di tutti i disegni
     */
    Vettore<std::unordered_map<std::string, std::string> > getTutteInfo() const;

    /**
     * @brief getNumeroDisegni      ritorna il numero di disegni presenti in workspace
     * @return                      unsigned int dei disegni attualmente prensenti
     */
    unsigned int getNumeroDisegni() const;

    /**
     * @brief getTuttiPunti         Ritorna un vettore con tutti i punti nel workspace
     * @return                      vettore di puntatori ai punti
     */
    const Vettore<Punto*> getTuttiPunti() const;

    /**
     * @brief getWorkspace          get del puntatore al workspace
     * @return                      il puntatore al workspace
     */
    WorkSpace* getWorkspace() const;

    /**
     * @brief getDisegni            get di tutti i disegni presenti in workspace attualmente
     * @return                      riferimento al vettore costante di DeepPtr a Disegnabile
     */
    const Vettore<DeepPtr<Disegnabile>>& getDisegni() const;

    /**
     * @brief addDisegnabile        aggiunge un Disegnabile* (generico) al workspace
     * @param                       puntatore al Disegnabile da aggiungere
     */
    void addDisegnabile(Disegnabile*) const;

    /**
     * @brief convertiOggettiJson   crea l'oggetto Disegno corretto a partire dal JSON ricevuto dal controller
     * @param disegnabile           oggetto QJsonObject contenente tutti i paramentri del disegno da importare
     */
    void convertiOggettiJson(const QJsonObject& disegnabile);
};

#endif // MODEL_H

#include "Controller.h"

#include <iostream>

Controller::Controller(QObject *parent) : QObject(parent) {}

void Controller::setModel(Model *m) { model = m; }

void Controller::setView(Interfaccia *v) { view = v; }

void Controller::refreshInfoDisegni() const {
    view->pulisciInfoDisegni();
    unsigned int cont = 1;
    for(auto&& i : model->getTutteInfo()){
        view->addInfoDisegnabile(i, cont);
        cont++;
    }
}

void Controller::showInfoDisegni() const {
    std::unordered_map<string, string> displayInfo;
    displayInfo = model->getInfoDisegnabile();
    view->addInfoDisegnabile(displayInfo, model->getNumeroDisegni());
}

void Controller::addPunto() const {
    try {
        Vettore<QString> dati = view->showNewPuntoDialog();
        if(!dati.empty()){
            string nome = dati[0].toStdString();
            if (nome == "")
                throw std::logic_error("Inserire un nome valido per il punto.");
            if(dati[1].contains(",") || dati[2].contains(","))
                throw std::logic_error("Per inserire un valore decimale usare il \".\". La \",\" non è accettata.");
            double x = dati[1].toDouble();
            double y = dati[2].toDouble();
            string c = dati[3].toStdString();
            model->addNewPunto(x, y, nome, c);
            showInfoDisegni();
            view->refreshPiano();
        }
    }  catch (std::runtime_error& exc) {
        view->showWarningDialog(exc.what());
    }  catch (std::logic_error& log) {
        view->showWarningDialog(log.what());
    }
}

void Controller::addSegmento() const {
    try {
        Vettore<Punto*> punti = model->getTuttiPunti();
        Vettore<QString> dati = view->showNewLineaDialog(punti, false);
        if(!dati.empty()){
            string nome         = dati[0].toStdString();
            unsigned int indexA = dati[1].toUInt();
            unsigned int indexB = dati[2].toUInt();
            string color        = dati[3].toStdString();
            model->addNewSegmento(punti[indexA], punti[indexB], nome, color);
            showInfoDisegni();
            view->refreshPiano();
        }
    } catch (std::runtime_error& exc) {
        view->showWarningDialog(exc.what());
    } catch (std::logic_error& log){
        view->showWarningDialog(log.what());
    }
}

void Controller::addRetta() const {
    try {
        Vettore<Punto*> punti = model->getTuttiPunti();
        Vettore<QString> dati = view->showNewLineaDialog(punti, true);
        if(!dati.empty()){
            string nome         = dati[0].toStdString();
            unsigned int indexA = dati[1].toUInt();
            unsigned int indexB = dati[2].toUInt();
            string color        = dati[3].toStdString();
            model->addNewRetta(punti[indexA], punti[indexB], nome, color);
            showInfoDisegni();
            view->refreshPiano();
        }
    } catch (std::runtime_error& exc) {
        view->showWarningDialog(exc.what());
    } catch (std::logic_error& log){
        view->showWarningDialog(log.what());
    }
}

void Controller::addCirconferenza() const {
    try {
        Vettore<Punto*> punti = model->getTuttiPunti();
        Vettore<QString> dati = view->showNewCirconferenzaDialog(punti);
        if(!dati.empty()){
            string nome         = dati[0].toStdString();
            unsigned int indexC = dati[1].toUInt();
            if(dati[2].contains(","))
                throw std::logic_error("Per inserire un valore decimale usare il \".\". La \",\" non è accettata.");
            double raggio = dati[2].toDouble();
            string color        = dati[3].toStdString();
            model->addNewCirconferenza(punti[indexC], raggio, nome, color);
            showInfoDisegni();
            view->refreshPiano();
        }
    } catch (std::runtime_error& exc) {
        view->showWarningDialog(exc.what());
    } catch (std::logic_error& log){
        view->showWarningDialog(log.what());
    }
}

void Controller::addEllisse() const {
    try {
        Vettore<Punto*> punti = model->getTuttiPunti();
        Vettore<QString> dati = view->showNewEllisseDialog(punti);
        if(!dati.empty()){
            string nome         = dati[0].toStdString();
            unsigned int indexC = dati[1].toUInt();
            if(dati[2].contains(",") || dati[3].contains(","))
                throw std::logic_error("Per inserire un valore decimale usare il \".\". La \",\" non è accettata.");
            double semiA        = dati[2].toDouble();
            double semiB        = dati[3].toDouble();
            string color        = dati[4].toStdString();
            model->addNewEllisse(punti[indexC], semiA, semiB, nome, color);
            showInfoDisegni();
            view->refreshPiano();
        }
    } catch (std::runtime_error& exc) {
        view->showWarningDialog(exc.what());
    } catch (std::logic_error& log){
        view->showWarningDialog(log.what());
    }
}

void Controller::addRegolare() const
{
    try {
        Vettore<Punto*> punti = model->getTuttiPunti();
        Vettore<QString> dati = view->showNewRegolareDialog(punti);
        if(!dati.empty()){
            string nome             = dati[0].toStdString();
            unsigned int indexA     = dati[1].toUInt();
            unsigned int indexB     = dati[2].toUInt();
            if(dati[3].contains("."))
                throw std::logic_error("Per favore inserire un numero intero positivo.");
            unsigned int numLati    = dati[3].toUInt();
            string color            = dati[4].toStdString();
            model->addNewRegolare(std::pair<Punto*, Punto*>(punti[indexA], punti[indexB]), numLati, nome, color);
            showInfoDisegni();
            view->refreshPiano();
        }
    } catch (std::runtime_error& exc) {
        view->showWarningDialog(exc.what());
    } catch (std::logic_error& log){
        view->showWarningDialog(log.what());
    }
}

void Controller::addPoligono() const
{
    try {
        Vettore<Punto*> punti = model->getTuttiPunti();
        Vettore<QString> dati = view->showNewPoligonoDialog(punti);
        if(!dati.empty()){
            if(punti.empty())
                throw std::runtime_error("Non hai punti sufficienti per creare il poligono.");
            string nome     = dati[0].toStdString();
            Vettore<Punto*> puntiScelti;
            for(unsigned int j = 1; j < dati.size()-1; j++){
                puntiScelti.push_back(punti[dati[j].toUInt()]);
            }
            string color    = (*(dati.end()-1)).toStdString();
            model->addNewPoligono(puntiScelti, nome, color);
            showInfoDisegni();
            view->refreshPiano();
        }
    } catch (std::runtime_error& exc) {
        view->showWarningDialog(exc.what());
    } catch (std::logic_error& log){
        view->showWarningDialog(log.what());
    }
}

void Controller::removeDisegno() const {
    try {
        unsigned int index = view->showRemoveDialog();
        model->removeDisegno(index-1);
        refreshInfoDisegni();
        view->refreshPiano();
    } catch (std::runtime_error& exc) {
        view->showWarningDialog(exc.what());
    } catch (std::out_of_range& exc) {
        view->showWarningDialog(exc.what());
    }
}

void Controller::cancellaTutto() const {
    int d = view->showConfermaDialog("Attenzione stai per eliminare tutti i disegni inseriti. L'operazione non è annullabile.");
    if(d == QMessageBox::Yes)
    {
        model->cancellaTutto();
        refreshInfoDisegni();
        view->refreshPiano();
    }
}

WorkSpace* Controller::getWorkspace() const {
    return model->getWorkspace();
}

void Controller::write(QJsonObject& jObj) const
{
    QJsonArray arrayDisegnabili;
    for (auto& v : model->getDisegni()) {
        QJsonObject disegnabile;
        v->write(disegnabile);
        arrayDisegnabili.append(disegnabile);
    }
    jObj["disegnabili"] = arrayDisegnabili;
}

void Controller::read(const QJsonObject& jObj) const
{
    model->cancellaTutto();
    refreshInfoDisegni();
    QJsonArray arrayDisegnabili = jObj["disegnabili"].toArray();
    for (int i=0; i<arrayDisegnabili.size(); ++i) {
        model->convertiOggettiJson(arrayDisegnabili[i].toObject());
        showInfoDisegni();
    }
    view->refreshPiano();
}

bool Controller::saveToFile() const
{
    try {
        QString fileName = view->showSaveFile();
        QFile saveFile(fileName);
        if (!saveFile.open(QIODevice::WriteOnly)) {
            throw std::runtime_error("Impossibile aprire il file.");
        }
        QJsonObject sessionObject;
        write(sessionObject);
        saveFile.write(QJsonDocument(sessionObject).toJson());
        return true;
    }  catch (std::runtime_error& e) {
        e.what();
        return false;
    }
}

void Controller::loadFromFile() const
{
    try {
        QFile loadFile(view->showLoadFile());
        if (!loadFile.open(QIODevice::ReadOnly))
            throw std::runtime_error("Impossibile aprire il file.");
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
        read(loadDoc.object());
    }  catch (std::runtime_error& e) {
        e.what();
    }
}

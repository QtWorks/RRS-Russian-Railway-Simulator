//------------------------------------------------------------------------------
//
//      Магистральный пассажирский электровоз переменного тока ЧС4т.
//      Дополнение для Russian Railway Simulator (RRS)
//
//      (c) RRS development team:
//          Дмитрий Притыкин (maisvendoo),
//          Николай Авилкин (avilkin.nick)
//
//      Дата: 16/06/2019
//
//------------------------------------------------------------------------------
#ifndef STEPSWITCH_H
#define STEPSWITCH_H

#include "device.h"
#include "km-21kr2-state.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class StepSwitch : public Device
{
public:

    ///Конструктор
    StepSwitch(QObject *parent = Q_NULLPTR);

    ///Деструктор
    ~StepSwitch();

    void setCtrlState(ControllerState ctrlState) { this->ctrlState = ctrlState; }

private:
    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);
    void load_config(CfgReader &cfg);
    void preStep(state_vector_t &Y, double t);
    void stepKeysControl(double t, double dt);


    ControllerState ctrlState;

    Trigger *rs;

    int steps;

//    double f1 - Y[0];
    double shaft_rel;

    double PI;
    double KL;
    double AB;
    double GH;
    double CD;
    double EF;
    double IJ;
    double NM;
    double UV;


    double s62;
    double s67;
    double s69;
    double s45;
    double s43;
    double s410;
};


#endif // STEPSWITCH_H

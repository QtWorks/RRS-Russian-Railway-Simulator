#include    "pneumo-splitter.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PneumoSplitter::PneumoSplitter(QObject *parent) : BrakeDevice(parent)
  , V0(1e-3)
  , Q_in(0.0)
  , Q_out1(0.0)
  , p_out1(0.0)
  , Q_out2(0.0)
  , p_out2(0.0)
{
    std::fill(K.begin(), K.end(), 0.0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
PneumoSplitter::~PneumoSplitter()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoSplitter::setQ_in(double value)
{
    Q_in = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoSplitter::setP_out1(double value)
{
    p_out1 = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoSplitter::setP_out2(double value)
{
    p_out2 = value;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double PneumoSplitter::getQ_out1() const
{
    return Q_out1;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double PneumoSplitter::getQ_out2() const
{
    return Q_out2;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
double PneumoSplitter::getP_in() const
{
    return getY(0);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoSplitter::preStep(state_vector_t &Y, double t)
{
    Q_out1 = K[1] * (Y[0] - p_out1) + K[4] * (p_out2 - p_out1);
    Q_out2 = K[2] * (Y[0] - p_out2) + K[4] * (p_out1 - p_out2);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoSplitter::ode_system(const state_vector_t &Y,
                                state_vector_t &dYdt,
                                double t)
{
    dYdt[0] = ( Q_in - K[3] *(Q_out1 + Q_out2) ) / V0;

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void PneumoSplitter::load_config(CfgReader &cfg)
{
    QString secName = "Device";

    for (size_t i = 1; i < K.size(); ++i)
    {
        QString coeff = QString("K%1").arg(i);
        cfg.getDouble(secName, coeff, K[i]);
    }

    cfg.getDouble(secName, "V0", V0);
}

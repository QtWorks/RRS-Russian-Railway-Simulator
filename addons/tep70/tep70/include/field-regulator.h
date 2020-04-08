#ifndef     FIELD_REGULATOR_H
#define     FIELD_REGULATOR_H

#include    "device.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class FieldRegulator : public Device
{
public:

    FieldRegulator(QObject *parent = Q_NULLPTR);

    ~FieldRegulator();

    /// Загрузить уставки из файла
    void load_settings(QString file_path);

private:

    /// Структура для хранения уставок регулятора на определенной позиции
    struct reg_settings_t
    {
        /// Номер позиции КМ
        int     pos_num;
        /// Частота вращения дизеля
        double  n_ref;
        /// Мощность, кВт
        double  P_ref;
        /// Ограничение напряжения, В
        double  U_max;
        /// Ограничение тока, А
        double  I_max;

        reg_settings_t()
            : pos_num(0)
            , n_ref(0.0)
            , P_ref(0.0)
            , U_max(0.0)
            , I_max(0.0)
        {

        }
    };

    /// Ошибка по мощности
    double  dP;

    /// Ошибка по напряжению
    double  dU;

    /// Ошибка по току
    double  dI;

    /// Текущее напряжение
    double  U;

    /// Текущий ток
    double  I;

    /// Текущая частота вращения вала генератора
    double  omega;

    /// Напряжение, выдаваемое возбудителем
    double  U_fg;

    /// Напряжение возбуждения ТГ
    double  Uf;

    enum
    {
        NUM_COEFS = 6
    };

    std::array<double, NUM_COEFS>   K;

    /// Уставки регулятора
    QMap<int, reg_settings_t>       reg_settings;

    void preStep(state_vector_t &Y, double t);

    void ode_system(const state_vector_t &Y, state_vector_t &dYdt, double t);

    void load_config(CfgReader &cfg);

    /// Вернуть уставку мощности на данной частоте вращения
    double getRefPower(double omega);
};

#endif // FIELD_REGULATOR_H
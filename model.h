#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QPair>
#include <QFloat16>

class CarModel : public QObject {
    Q_OBJECT

public:
        explicit CarModel(QObject *parent=nullptr);

        void update(const int elapsed);
        void accel(const bool more);
        void rotate(const bool left);
        void reset(const qfloat16 x, const qfloat16 y);

        const qfloat16 getX() const;
        const qfloat16 getY() const;
        const qfloat16 getD() const;

private:
        qfloat16 speed;
        qfloat16 direction;

        QPair<qfloat16, qfloat16> position;
};

#endif // MODEL_H

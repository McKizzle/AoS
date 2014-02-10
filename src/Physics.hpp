#ifndef PHYSICS_H
#define PHYSICS_H
namespace aos {
    class Integrator
    {
        public:
            virtual void integrate() = 0;
            virtual void overrided() = 0;
    };

    class PhysicsGine: public Integrator
    {
        public:
            PhysicsGine();
            ~PhysicsGine();
            virtual void integrate();
            virtual void overrided();
    };
}
#endif

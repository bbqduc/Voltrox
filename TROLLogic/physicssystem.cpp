#include "physicssystem.h"
#include <TROLCommon/root.h>

PhysicsSystem::PhysicsSystem()
    :
        ISystem(CTFlags::PHYSICS),
        broadphase(),
        collisionConfiguration(),
        solver(),
        dispatcher(&collisionConfiguration),
        dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration),
        gravity(0,0,0)
{
    dynamicsWorld.setGravity(gravity);
    //	dynamicsWorld.setInternalTickCallback(myTickCallback, static_cast<void*>(this));
}

/*void PhysicsSystem::updatePositions(ct_t selection)
  {
  std::vector<entid_t> entities = getAllEntities(selection);
  for(int i = 0; i < entities.size(); ++i)
  {
  Position *p = getComponent(entities[i], CT_POSITION);
  PhysicsComponent *c = getComponent(entities[i], CT_PHYSICS);
  p->transform = c->getWorldTransform(); // TODO : what if just point straight to it :ooo
  }
  }*/

rsp_t PhysicsSystem::handleMessage(Message msg)
{
    btRigidBody *c;
    if(msg.mType != ADD)
        c = static_cast<btRigidBody*>(Root::storageSystem.getComponent(msg.entity, CT_PHYSICS)); // TODO : what if add
    switch(msg.mType)
    {
        case ADD:
            {
                PhysCreateMsgData* create = static_cast<PhysCreateMsgData*>(msg.data);
                c = new (Root::storageSystem.addComponent(msg.entity, CT_PHYSICS)) btRigidBody(create->ci);
                c->setWorldTransform(create->t);
                Message posm = {PHYS_ADD_LINK, msg.entity, &c->getWorldTransform()};
                Root::broadcastMessage(posm, CTFlags::POSITION);
                dynamicsWorld.addRigidBody(c);
                return MSG_DONE;
            }
        case REMOVE:
            dynamicsWorld.removeRigidBody(c);
            Root::storageSystem.removeComponent(msg.entity, CT_PHYSICS);
            return MSG_DONE;
        case PHYS_THRUSTERS:
            {
                btVector3 relF(0,0,*static_cast<float*>(msg.data));
                btMatrix3x3& entityRot = c->getWorldTransform().getBasis();
                btVector3 corF = entityRot * relF;
                c->setActivationState(true);
                c->applyCentralImpulse(corF);
                return MSG_DONE;
            }
        case PHYS_BRAKES:
            {
                btVector3 a = c->getAngularVelocity();
                btVector3 l = c->getLinearVelocity();
                a *= 0.99f;
                l *= 0.99f;
                c->setAngularVelocity(a);
                c->setLinearVelocity(l);
                return MSG_DONE;
            }
        case PHYS_ROTATE:
            {
                btVector3* relF = static_cast<btVector3*>(msg.data);
                btMatrix3x3& entityRot = c->getWorldTransform().getBasis();
                btVector3 corF = entityRot * *relF;
                c->setActivationState(true);
                c->applyTorqueImpulse(corF);
                return MSG_DONE;
            }
        case PHYS_SET_COLLISION_FLAGS:
            c->setCollisionFlags(*static_cast<btRigidBody::CollisionFlags*>(msg.data));
            return MSG_DONE;
        default:
            return MSG_IGNORED;
    }
}

void PhysicsSystem::tick()
{
    // TODO : COLLISION CALLBACK -> SEND EVENTS TO OTHER SYSTEMS
    dynamicsWorld.stepSimulation(1/60.0f, 10);
}

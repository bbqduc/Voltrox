#include "physicssystem.h"
#include <TROLCommon/root.h>

PhysicsSystem::PhysicsSystem()
    :
        System<btRigidBody>(CTFlags::PHYSICS),
        broadphase(),
        collisionConfiguration(),
        solver(),
        dispatcher(&collisionConfiguration),
        dynamicsWorld(&dispatcher, &broadphase, &solver, &collisionConfiguration),
        gravity(0,0,0)
{
    dynamicsWorld.setGravity(gravity);
    //	dynamicsWorld.setInternalTickCallback(myTickCallback, static_cast<void*>(this));

    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0),1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0,1),btVector3(0,-1,0)));
    btRigidBody::btRigidBodyConstructionInfo
        groundRigidBodyCI(0,groundMotionState,groundShape,btVector3(0,0,0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld.addRigidBody(groundRigidBody);
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
        *c = getComponent(msg.entity); // TODO : what if add
    switch(msg.mType)
    {
        case ADD:
            {
                PhysCreateMsgData* create = static_cast<PhysCreateMsgData*>(msg.data);
                c = new (addComponent(msg.entity)) btRigidBody(create->ci);
                c->setWorldTransform(create->t);
                Message posm = {PHYS_ADD_LINK, msg.entity, &c->getWorldTransform()};
                Root::broadcastMessage(posm, CTFlags::POSITION);
                dynamicsWorld.addRigidBody(c);
                return MSG_DONE;
            }
        case REMOVE:
            dynamicsWorld.removeRigidBody(c);
            removeComponent(msg.entity);
            return MSG_DONE;
        case PHYS_THRUSTERS:
            {
                btVector3 v(0,*static_cast<float*>(msg.data),0);
                c->applyForce(v, btVector3(0,0,0));
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

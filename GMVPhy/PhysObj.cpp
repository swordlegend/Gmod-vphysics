#include "PhysObj.h"

#include <GarrysMod/Lua/Interface.h>
#include <vphysics_interface.h>
#include "../include/vphysics_interfaceV32.h"

#include "MiscFuncs.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

using namespace GarrysMod::Lua;

//
// Name: PhysObj:ApplyTorqueCenter
// Desc: Applies a torque to the center of an object
// Arg1: Vector|torque|Torque impulse in kg * degrees/s
// Ret1:
//
int lPhysObjApplyTorqueCenter(lua_State *state) {
	IPhysicsObject32 *	pObject = Get_PhysObj(state, 1);
	Vector *			pVec = Get_Vector(state, 2);

	if (pObject && pVec)
		pObject->ApplyTorqueCenter(*pVec);

	return 0;
}

//
// Name: PhysObj:SetLocalGravity
// Desc: Sets an object's gravity. You must disable the environment's gravity with EnableGravity(false) first!
// Arg1: Vector|gravityVec|The gravity vector
// Ret1:
//
int lPhysObjSetLocalGravity(lua_State *state) {
	IPhysicsObject32 *	pObject = Get_PhysObj(state, 1);
	Vector *			pVec = Get_Vector(state, 2);

	if (pVec)
		pObject->SetLocalGravity(*pVec);

	return 0;
}

//
// Name: PhysObj:GetLocalGravity
// Desc: Gets the object's current gravity. Will return the same gravity as the environment if you didn't set it previously.
// Arg1:
// Ret1: Vector|gravityVec|The gravity vector
//
int lPhysObjGetLocalGravity(lua_State *state) {
	IPhysicsObject32 *pObject = Get_PhysObj(state, 1);

	Vector grav = pObject->GetLocalGravity();
	Push_Vector(state, grav);

	return 1;
}

//
// Name: PhysObj:GetEnvironment
// Desc: Returns the object's current physics environment
// Arg1:
// Ret1: PhysEnv|env|Environment
//
/*
int lPhysObjGetEnvironment(lua_State *state) {
	IPhysicsObject32 *pObj = Get_PhysObj(state, 1);

	IPhysicsEnvironment32 *pEnv = pObj->GetVPhysicsEnvironment();
	Push_PhysEnv(state, pEnv);

	return 1;
}
*/

//
// Name: PhysObj:SetAngleVelocity
// Desc: Sets the object's angular velocity (in local space)
// Arg1: Vector|vel|The new angular velocity
// Ret1: 
//
int lPhysObjSetAngleVelocity(lua_State *state) {
	IPhysicsObject32 *pObject = Get_PhysObj(state, 1);
	Vector *pAngVel = Get_Vector(state, 2);

	if (pAngVel)
		pObject->SetVelocity(NULL, pAngVel);

	return 0;
}

//
// Name: PhysObj:GetCollide
// Desc: Gets the object's current collision mesh.
// Arg1:
// Ret1: CPhysCollide|collide|The collision mesh
//
int lPhysObjGetCollide(lua_State *state) {
	IPhysicsObject32 *pObject = Get_PhysObj(state, 1);

	CPhysCollide *pCollide = pObject->GetCollide();
	Push_PhysCollide(state, pCollide);
	
	return 1;
}

int lPhysObjSetCollide(lua_State *state) {
	IPhysicsObject32 *pObject = Get_PhysObj(state, 1);
	CPhysCollide *pCollide = Get_PhysCollide(state, 2);

	pObject->SetCollide(pCollide);
	return 0;
}

int lPhysObjGetVehicleController(lua_State *state) {
	IPhysicsObject32 *pObject = Get_PhysObj(state, 1);

	IPhysicsVehicleController *pController = pObject->GetVehicleController();
	if (!pController) {
		LUA->PushNil();
		return 1;
	}

	Push_PhysVehicleController(state, pController);
	return 1;
}

int Init_PhysObj(lua_State *state) {
	LUA->PushSpecial(SPECIAL_REG);
		LUA->GetField(-1, "PhysObj");
			LUA->PushCFunction(lPhysObjApplyTorqueCenter);	LUA->SetField(-2, "ApplyTorqueCenter");
			LUA->PushCFunction(lPhysObjSetLocalGravity);	LUA->SetField(-2, "SetLocalGravity");
			LUA->PushCFunction(lPhysObjGetLocalGravity);	LUA->SetField(-2, "GetLocalGravity");
			LUA->PushCFunction(lPhysObjSetAngleVelocity);	LUA->SetField(-2, "SetAngleVelocity");
			LUA->PushCFunction(lPhysObjGetCollide);			LUA->SetField(-2, "GetCollide");
			LUA->PushCFunction(lPhysObjSetCollide);			LUA->SetField(-2, "SetCollide");
			LUA->PushCFunction(lPhysObjGetVehicleController); LUA->SetField(-2, "GetVehicleController");
	LUA->Pop(2);

	return 0;
}
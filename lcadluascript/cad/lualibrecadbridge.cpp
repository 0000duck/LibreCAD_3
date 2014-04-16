extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "lualibrecadbridge.h"

#include "lua-intf/LuaIntf.h"
#include "lua-intf/LuaIntf/QtLuaIntf.h"

#include <cad/geometry/geocoordinate.h>
#include <cad/primitive/line.h>
#include <cad/primitive/circle.h>
#include <cad/document/abstractdocument.h>
#include <cad/dochelpers/documentimpl.h>
#include <cad/operations/create.h>

namespace LuaIntf {
    LUA_USING_SHARED_PTR_TYPE(boost::shared_ptr)
}

using namespace LuaIntf;
using namespace lc;


void lua_openlckernel(lua_State * L)
{

    LuaBinding(L)
            .beginClass <operation::Operation> ("Operation")
            .addFunction("execute", &operation::Operation::execute)
            .endClass ()

            .beginClass <ID> ("ID")
            .addFunction("id", &ID::id)
            .endClass ()

            .beginExtendClass <CADEntity, ID> ("CADEntity")
            .endClass ()

            .beginClass <geo::Vector> ("Vector")
            .addConstructor(LUA_SP(shared_ptr<const geo::Vector>), LUA_ARGS(const geo::Coordinate& start, const geo::Coordinate& end))
            .endClass ()

            .beginClass <AbstractDocument> ("AbstractDocument")
            .endClass ()

            .beginClass<geo::Coordinate>("Coord")
            .addConstructor(LUA_ARGS(double x, double y))
            .addFunction("x", &geo::Coordinate::x)
            .addFunction("y", &geo::Coordinate::y)
            .addFunction("z", &geo::Coordinate::z)
            .endClass()

            .beginClass<geo::Coordinate>("Coordinate")
            .addConstructor(LUA_ARGS(double x, double y))
            .addFunction("x", &geo::Coordinate::x)
            .addFunction("y", &geo::Coordinate::y)
            .addFunction("z", &geo::Coordinate::z)
            .endClass()

            .beginExtendClass <Line, CADEntity> ("Line")
            .addConstructor(LUA_SP(shared_ptr< Line>), LUA_ARGS(const geo::Coordinate& start, const geo::Coordinate& end))
            .endClass()

            .beginExtendClass <Circle, CADEntity> ("Circle")
            .addConstructor(LUA_SP(shared_ptr< Circle>), LUA_ARGS(const geo::Coordinate& center, double radius))
            .endClass()

            .beginExtendClass <LuaLcOperationCreate, operation::Operation> ("Create")
            .addConstructor(LUA_SP(shared_ptr<LuaLcOperationCreate>), LUA_ARGS(AbstractDocument* document, const QString& layerName))
            .addFunction ("append", &LuaLcOperationCreate::append)
            .endClass()

            .beginExtendClass <LuaLcOperationRotate, operation::Operation> ("Rotate")
            .addConstructor(LUA_SP(shared_ptr<LuaLcOperationRotate>), LUA_ARGS(lc::AbstractDocument* document, const geo::Coordinate& rotation_center, const double rotation_angle, const long no_copies))
            .addFunction ("append", &LuaLcOperationRotate::append)
            .endClass()

            .beginClass <DocumentImpl> ("DocumentImpl")
            .endClass ()

            .beginClass <QString> ("QString")
            .addConstructor(LUA_ARGS(const char *))
            .endClass ();

}

// .addConstructor(LUA_SP(shared_ptr<const CreateEntities>), LUA_ARGS(AbstractDocument * doc))


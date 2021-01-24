/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
*/

#include "SimpleDotVisitor.h"


namespace osgDot {

    constexpr const char PROBE_UNIFORM[] = "probe";
    constexpr const char SPECTRAL_FILTER_TAG[] = "spectral_filter";
    constexpr const char POSITION_NODE_TAG[] = "position_node";
    constexpr const char ROOT_NODE_TAG[] = "root_node";
	
SimpleDotVisitor::SimpleDotVisitor()
{
}

SimpleDotVisitor::~SimpleDotVisitor()
{
}


void SimpleDotVisitor::handle(osg::StateSet& stateset, int id)
{
    std::stringstream label;
    label << "<top> " << stateset.className();
    

    if (stateset.getUniformList().size() > 0)
    {
        label << " | " << stateset.getName() << " | ";
        const osg::StateSet::UniformList& ul = stateset.getUniformList();
        for (osg::StateSet::UniformList::const_iterator itr = ul.begin();
            itr != ul.end();
            ++itr)
        {
            bool res = false;

            auto statesetUniform = itr->second.first;
            std::string uniform_type = statesetUniform->getTypename(statesetUniform->getType());
            unsigned int elements_num = statesetUniform->getInternalArrayNumElements();
            
            if (elements_num == 1)
            {
                if (statesetUniform->getType() == GL_INT)
                {
                    int int_val;
                    res = statesetUniform->get(int_val);
                    if (res)
                    {
                        label
                            << "[#" << statesetUniform->getNameID() << "] "
                            << " " << statesetUniform->getName() 
                            << " (" << uniform_type << ") "
                            << " = " << int_val
                            << " | ";
                    }
                }

                else if (statesetUniform->getType() == GL_BOOL)
                {
                   
                  
                    if (stateset.getUniformList().size() == 1 &&
                        stateset.getUniformList().find(PROBE_UNIFORM) != stateset.getUniformList().end())
                    {
                        return;
                    }

                    if (statesetUniform->getName() == PROBE_UNIFORM)
                    {
                        continue;
                    }


                    bool bool_val;
                    res = statesetUniform->get(bool_val);
                    if (res)
                    {
                        label
                            << "[#" << statesetUniform->getNameID() << "] "
                            << " " << statesetUniform->getName()
                            << " (" << uniform_type << ") "
                            << " = " << bool_val
                            << " | ";
                    }
                    
                }        

                else if (statesetUniform->getType() == GL_FLOAT)
                {
                    float float_val;
                    res = statesetUniform->get(float_val);
                    if (res)
                    {
                        label
                            << "[#" << statesetUniform->getNameID() << "] "
                            << " " << statesetUniform->getName()
                            << " (" << uniform_type << ") "
                            << " = " << float_val
                            << " | ";
                    }
                }
               
                else if (statesetUniform->getType() == GL_DOUBLE)
                {
                    double double_val;
                    res = statesetUniform->get(double_val);
                    if (res)
                    {
                        label
                            << "[#" << statesetUniform->getNameID() << "] "
                            << " " << statesetUniform->getName()
                            << " (" << uniform_type << ") "
                            << " = " << double_val
                            << " | ";
                    }
                }
                
                else if (statesetUniform->getType() == GL_UNSIGNED_INT)
                {
                    unsigned int uint_val;
                    res = statesetUniform->get(uint_val);
                    if (res)
                    {
                        label
                            << "[#" << statesetUniform->getNameID() << "] "
                            << " " << statesetUniform->getName()
                            << " (" << uniform_type << ") "
                            << " = " << uint_val
                            << " | ";
                    }
                }                
            }
            else
            {
                std::string values{};
                if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_FLOAT)
                {
                    osg::FloatArray* _floatArray = statesetUniform->getFloatArray();


                    for (osg::FloatArray::iterator itr = _floatArray->begin(); itr != _floatArray->end(); ++itr)
                        values += std::to_string(*itr);

                    label
                        << "[#" << statesetUniform->getNameID() << "] "
                        << " " << statesetUniform->getName()
                        << " (" << uniform_type << ") "
                        << " = " << values
                        << " | ";
                }
                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_DOUBLE)
                {

                    osg::DoubleArray* _doubleArray = statesetUniform->getDoubleArray();
                    for (int i = 0; i <= _doubleArray->getNumElements() - 1; i++)
                        values += std::to_string((*_doubleArray)[i]) + ", ";

                    label
                        << "[#" << statesetUniform->getNameID() << "] "
                        << " " << statesetUniform->getName()
                        << " (" << uniform_type << ") "
                        << " = " << values
                        << " | ";
                   
                }
                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_INT)
                {
                    osg::IntArray* _intArray = statesetUniform->getIntArray();
                    for (int i = 0; i <= _intArray->getNumElements() - 1; i++)
                        values += std::to_string((*_intArray)[i]) + ", ";
                    

                    for (osg::IntArray::iterator itr = _intArray->begin(); itr != _intArray->end(); ++itr)
                        values += std::to_string(*itr);

                    label
                        << "[#" << statesetUniform->getNameID() << "] "
                        << " " << statesetUniform->getName()
                        << " (" << uniform_type << ") "
                        << " = " << values
                        << " | ";
                }
                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_UNSIGNED_INT)
                {
                    
                    osg::UIntArray* _uintArray = statesetUniform->getUIntArray();
                    for (int i = 0; i <= _uintArray->getNumElements() - 1; i++)
                        values += std::to_string((*_uintArray)[i]) + ", ";

                    for (osg::UIntArray::iterator itr = _uintArray->begin(); itr != _uintArray->end(); ++itr)
                        values += std::to_string(*itr);

                    label
                        << "[#" << statesetUniform->getNameID() << "] "
                        << " " << statesetUniform->getName()
                        << " (" << uniform_type << ") "
                        << " = " << values
                        << " | ";
                }

                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_INT64_ARB)
                {
                    osg::Int64Array* _int64Array = statesetUniform->getInt64Array();                    
                    for (int i = 0; i <= _int64Array->getNumElements() - 1; i++)
                        values += std::to_string((*_int64Array)[i]) + ", ";

                    for (osg::Int64Array::iterator itr = _int64Array->begin(); itr != _int64Array->end(); ++itr)
                        values += std::to_string(*itr);

                    label
                        << "[#" << statesetUniform->getNameID() << "] "
                        << " " << statesetUniform->getName()
                        << " (" << uniform_type << ") "
                        << " = " << values
                        << " | ";

                }

                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_UNSIGNED_INT64_ARB)
                {
                    osg::UInt64Array* _uint64Array = statesetUniform->getUInt64Array(); 
                    for (int i = 0; i <= _uint64Array->getNumElements() - 1; i++)
                        values += std::to_string((*_uint64Array)[i]) + ", ";
                    
                    for (osg::UInt64Array::iterator itr = _uint64Array->begin(); itr != _uint64Array->end(); ++itr)
                        values += std::to_string(*itr);

                    label
                        << "[#" << statesetUniform->getNameID() << "] "
                        << " " << statesetUniform->getName()
                        << " (" << uniform_type << ") "
                        << " = " << values
                        << " | ";
                }
            }
        }
    }

    drawNode( id, "record", "solid, filled", label.str(), "mediumpurple2", "gray15" );
}

void SimpleDotVisitor::handle(osg::Drawable& drawable, int id)
{
    std::stringstream label;
    label << "<top> " << drawable.className();
    if ( !drawable.getName().empty() ) { label << " | " << drawable.getName(); }
    drawNode( id, "record", "solid, filled", label.str(), "cornflowerblue", "black" );
}

void SimpleDotVisitor::handle(osg::Node& node, int id)
{
    
    std::stringstream label;
   
    label << "<top> "<<node.className();
    if ( !node.getName().empty() ) { label << " | " << node.getName(); }
    
    drawNode(id, "Mrecord", "solid, filled", label.str(), "cornflowerblue", "black");
}

void SimpleDotVisitor::handle(osg::Group& node, int id)
{
    std::stringstream label;
    label << "<top> " << node.className();
    if ( !node.getName().empty() ) { label << " | " << node.getName(); }
    
    if (node.getName().find(ROOT_NODE_TAG) != std::string::npos) {
        drawNode(id, "Mrecord", "solid, filled", label.str(), "coral", "black");
    }    
    else if (node.getName().find(POSITION_NODE_TAG) != std::string::npos) {
        drawNode(id, "Mrecord", "solid, filled", label.str(), "red1", "black");
    }
    else if (node.getName().find(SPECTRAL_FILTER_TAG) != std::string::npos) {
        drawNode(id, "Mrecord", "solid, filled", label.str(), "darkseagreen3", "black");
    }
    else
    {
        drawNode(id, "Mrecord", "solid, filled", label.str(), "cornflowerblue", "black");
    }
}

void SimpleDotVisitor::handle(osg::Node&, osg::StateSet& stateset, int parentID, int childID )
{
    if (stateset.getUniformList().size() == 1 &&
        stateset.getUniformList().find(PROBE_UNIFORM) != stateset.getUniformList().end())
    {
        return;
    }
        

    drawEdge( parentID, childID, "solid", "mediumpurple2" );
}

void SimpleDotVisitor::handle(osg::Drawable&, osg::StateSet&, int parentID, int childID )
{
    drawEdge( parentID, childID, "solid", "mediumpurple2" );
}

void SimpleDotVisitor::handle(osg::Group&, osg::Node&, int parentID, int childID )
{
    drawEdge( parentID, childID, "dashed" );
}

void SimpleDotVisitor::drawNode( int id, const std::string& shape, const std::string& style, const std::string& label, const std::string& color, const std::string& fillColor )
{
    _nodes << id <<
        "[shape=\"" << shape <<
        "\" ,label=\"" << label <<
        "\" ,style=\"" << style <<
        "\" ,color=\"" << color <<
        "\" ,fontname=\"" << "AvantGarde - Demi"  <<
        "\" ,fontcolor=\"" << fillColor <<
        "\"]" << std::endl;
}

void SimpleDotVisitor::drawEdge( int sourceId, int sinkId, const std::string& style, const std::string& color)
{   
    _edges
        << sourceId << ":top -> "
        << sinkId   << ":top [style=\"" << style <<
        "\" ,color=\"" << color <<
        "\" ,arrowsize=\"" << ".7" <<                
        "\"]" << std::endl;
}

} // namespace osgDot

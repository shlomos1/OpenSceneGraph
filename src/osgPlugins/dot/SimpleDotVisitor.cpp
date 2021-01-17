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
                
                if (statesetUniform->getType() == GL_BOOL)
                {
                    bool bool_val;
                    res = statesetUniform->get(bool_val);
                    if (res)
                    {
                        label   << statesetUniform->getName()                   // uniform name
                                << " , id = " << statesetUniform->getNameID()   // uniform unique id
                                << " [" << uniform_type << "] "                 // uniform type                                
                                << " = " << bool_val                            // uniform value
                                << " | ";
                    }
                }               
                else if (statesetUniform->getType() == GL_FLOAT)
                {
                    float float_val;
                    res = statesetUniform->get(float_val);
                    if (res)
                    {
                        label << statesetUniform->getName()                   // uniform name
                            << " , id = " << statesetUniform->getNameID()   // uniform unique id
                            << " [" << uniform_type << "] "                 // uniform type                                
                            << " = " << float_val                            // uniform value
                            << " | ";
                    }
                }
               
                else if (statesetUniform->getType() == GL_DOUBLE)
                {
                    float double_val;
                    res = statesetUniform->get(double_val);
                    if (res)
                    {
                        label << statesetUniform->getName()                   // uniform name
                            << " , id = " << statesetUniform->getNameID()   // uniform unique id
                            << " [" << uniform_type << "] "                 // uniform type                                
                            << " = " << double_val                            // uniform value
                            << " | ";
                    }
                }

                else if (statesetUniform->getType() == GL_INT)
                {
                    float int_val;
                    res = statesetUniform->get(int_val);
                    if (res)
                    {
                        label << statesetUniform->getName()                   // uniform name
                            << " , id = " << statesetUniform->getNameID()   // uniform unique id
                            << " [" << uniform_type << "] "                 // uniform type                                
                            << " = " << int_val                            // uniform value
                            << " | ";
                    }
                }

                else if (statesetUniform->getType() == GL_UNSIGNED_INT)
                {
                    float uint_val;
                    res = statesetUniform->get(uint_val);
                    if (res)
                    {
                        label << statesetUniform->getName()                   // uniform name
                            << " , id = " << statesetUniform->getNameID()   // uniform unique id
                            << " [" << uniform_type << "] "                 // uniform type                                
                            << " = " << uint_val                            // uniform value
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

                    label << statesetUniform->getName()                      // uniform name
                        << " , id = " << statesetUniform->getNameID()      // uniform unique id
                        << " [" << uniform_type  << "] "      // number of elements in unifom array                               
                        << " = " << values                            // uniform value
                        << " | ";                  
                }
                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_DOUBLE)
                {

                    osg::DoubleArray* _doubleArray = statesetUniform->getDoubleArray();
                    for (int i = 0; i <= _doubleArray->getNumElements() - 1; i++)
                        values += std::to_string((*_doubleArray)[i]) + ",";

                    label << statesetUniform->getName()                             // uniform name
                        << " , id = " << statesetUniform->getNameID()               // uniform unique id
                        << " [" << uniform_type << "] "      // number of elements in unifom array                               
                        << " = " << values                                          // uniform value
                        << " | ";
                   
                }
                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_INT)
                {
                    osg::IntArray* _intArray = statesetUniform->getIntArray();
                    for (int i = 0; i <= _intArray->getNumElements() - 1; i++)
                        values += std::to_string((*_intArray)[i]) + ",";
                    

                    for (osg::IntArray::iterator itr = _intArray->begin(); itr != _intArray->end(); ++itr)
                        values += std::to_string(*itr);

                    label << statesetUniform->getName()                      // uniform name
                        << " , id = " << statesetUniform->getNameID()      // uniform unique id
                        << " [" << uniform_type << "] "      // number of elements in unifom array                               
                        << " = " << values                            // uniform value
                        << " | ";
                }
                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_UNSIGNED_INT)
                {
                    
                    osg::UIntArray* _uintArray = statesetUniform->getUIntArray();
                    for (int i = 0; i <= _uintArray->getNumElements() - 1; i++)
                        values += std::to_string((*_uintArray)[i]) + ",";

                    for (osg::UIntArray::iterator itr = _uintArray->begin(); itr != _uintArray->end(); ++itr)
                        values += std::to_string(*itr);

                    label << statesetUniform->getName()                      // uniform name
                        << " , id = " << statesetUniform->getNameID()      // uniform unique id
                        << " [" << uniform_type << "] "      // number of elements in unifom array                               
                        << " = " << values                            // uniform value
                        << " | ";
                }

                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_INT64_ARB)
                {
                    osg::Int64Array* _int64Array = statesetUniform->getInt64Array();                    
                    for (int i = 0; i <= _int64Array->getNumElements() - 1; i++)
                        values += std::to_string((*_int64Array)[i]) + ",";

                    for (osg::Int64Array::iterator itr = _int64Array->begin(); itr != _int64Array->end(); ++itr)
                        values += std::to_string(*itr);

                    label << statesetUniform->getName()                      // uniform name
                        << " , id = " << statesetUniform->getNameID()      // uniform unique id
                        << " [" << uniform_type << "] "      // number of elements in unifom array                               
                        << " = " << values                            // uniform value
                        << " | ";

                }

                else if (statesetUniform->getInternalArrayType(statesetUniform->getType()) == GL_UNSIGNED_INT64_ARB)
                {
                    osg::UInt64Array* _uint64Array = statesetUniform->getUInt64Array(); 
                    for (int i = 0; i <= _uint64Array->getNumElements() - 1; i++)
                        values += std::to_string((*_uint64Array)[i]) + ",";
                    
                    for (osg::UInt64Array::iterator itr = _uint64Array->begin(); itr != _uint64Array->end(); ++itr)
                        values += std::to_string(*itr);

                    label << statesetUniform->getName()                             // uniform name
                        << " , id = " << statesetUniform->getNameID()               // uniform unique id
                        << " [" << uniform_type << "] "      // number of elements in unifom array                               
                        << " = " << values                                          // uniform value
                        << " | ";
                }
            }
        }
    }

    drawNode( id, "Mrecord", "solid, filled", label.str(), "orange", "black" );
}

void SimpleDotVisitor::handle(osg::Drawable& drawable, int id)
{
    std::stringstream label;
    label << "<top> " << drawable.className();
    if ( !drawable.getName().empty() ) { label << " | " << drawable.getName(); }
    drawNode( id, "record", "solid, filled", label.str(), "lightblue", "black" );
}

void SimpleDotVisitor::handle(osg::Node& node, int id)
{
    std::stringstream label;
    label << "<top> "<<node.className();
    if ( !node.getName().empty() ) { label << " | " << node.getName(); }
    drawNode( id, "record", "solid, filled", label.str(), "lightblue", "black" );
}

void SimpleDotVisitor::handle(osg::Group& node, int id)
{
    std::stringstream label;
    label << "<top> " << node.className();
    if ( !node.getName().empty() ) { label << " | " << node.getName(); }
    drawNode( id, "record", "solid, filled", label.str(), "lightblue", "black" );
}

void SimpleDotVisitor::handle(osg::Node&, osg::StateSet&, int parentID, int childID )
{
    drawEdge( parentID, childID, "" );
}

void SimpleDotVisitor::handle(osg::Drawable&, osg::StateSet&, int parentID, int childID )
{
    drawEdge( parentID, childID, "" );
}

void SimpleDotVisitor::handle(osg::Group&, osg::Node&, int parentID, int childID )
{
    drawEdge( parentID, childID, "" );
}

void SimpleDotVisitor::drawNode( int id, const std::string& shape, const std::string& style, const std::string& label, const std::string& color, const std::string& fillColor )
{
    _nodes << id <<
        "[shape=\"" << shape <<
        "\" ,label=\"" << label <<
        "\" ,style=\"" << style <<
        "\" ,color=\"" << color <<
        "\" ,fontname=\"" << "AvantGarde - Demi"  <<
        "\" ,fillColor=\"" << fillColor <<
        "\"]" << std::endl;
}

void SimpleDotVisitor::drawEdge( int sourceId, int sinkId, const std::string& style )
{
    _edges
        << sourceId << ":top -> "
        << sinkId   << ":top [style=\""
        << style    << "\"];"
        << std::endl;
}

} // namespace osgDot

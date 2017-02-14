/*
 *       /\
 *      /__\       Nicolas Pignet (C) 2017
 *     /_\/_\      École Nationale des Ponts et Chaussées - CERMICS
 *    /\    /\
 *   /__\  /__\    Gmsh tools
 *  /_\/_\/_\/_\
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * If you use this code for scientific publications, you are required to
 * cite it.
 */

#ifndef GMSHDATA_H
#define GMSHDATA_H

 #include<vector>
 #include<string>
 #include<utility>

class Data
{
  protected:
     size_t m_index;
     std::vector<double> m_data;

  public:
     Data();
     Data(const size_t index, const std::vector<double>& data);
     size_t getNbComposante() const;
     std::vector<double> getData() const;
     size_t getIndex() const;
     void changeData(const size_t indice, const double value);
     void changeData(const std::vector<double>& data);
     void changeIndex(const size_t index);
};

class SubData : public Data
{
   private:
      Node m_node;

   public:
      SubData();
      SubData(const std::vector<double>& data, const Node& node);
      SubData(const Data& data, const Node& node);
      Node getNode() const;
      void changeCoordinates(const std::vector<double>& coor);
      void changeIndex(const size_t index);

};


class GenericData
{
   protected:
      size_t m_composante;
      std::vector<Data> m_datas;
      double m_time_value;
      std::string m_title;

   public:
      GenericData();
      GenericData(const std::vector<Data>& datas);
      GenericData(const std::vector<Data>& datas, const double time_value, const std::string title);
      std::vector<Data>getData() const;
      double getTime() const;
      std::string getTitle() const;
      size_t getNbComposante() const;
      void changeNbComposante(const size_t nbcompo);
      void changeTime(const double time);
      void changeTitle(const std::string title);
      void addData(const Data& data);
      void addData(const size_t index, const std::vector<double>& values);
};


class NodeData : public GenericData
{
  private:
     void writeNodeData(const std::string name_mesh) const;

  public:
       void saveNodeData(const std::string name_mesh, const Gmesh& mesh) const;
};

class ElementData : public GenericData
{
  private:
     void writeElementData(const std::string name_mesh) const;

  public:
       void saveElementData(const std::string name_mesh, const Gmesh& mesh) const;
};

class ElementNodeData : public GenericData
{
  private:
     void writeElementNodeData(const std::string name_mesh) const;

  public:
       void saveElementNodeData(const std::string name_mesh, const Gmesh& mesh) const;
};

#endif
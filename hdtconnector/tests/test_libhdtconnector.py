import unittest
from hdtconnector.libhdtconnector import HDTConnector
from hdtconnector.libhdtconnector import triple_role

m_file = "etc/test.hdt"

class TestHDTConnector(unittest.TestCase):
  def test_basic_hdt(self):
    m_map = HDTConnector(m_file)
    iter = m_map.search("", "", "")
    while iter.has_next():
      print( iter.next().get_subject() )

  def test_should_iterate_hdt_file_getting_ids(self):
    m_map = HDTConnector(m_file)
    iter = m_map.search_id("", "", "")
    while iter.has_next():
      print( iter.next().get_subject() )

  def test_should_iterate_hdt_file_by_using_ids_in_search(self):
    m_map = HDTConnector(m_file)
    iter = m_map.search_id("", "", "")
    triple = iter.next()
    iter = m_map.search_id(triple.get_subject(), triple.get_predicate(), triple.get_object())
    while iter.has_next():
      print( iter.next().get_subject() )

  def test_should_transform_id_into_url(self):
    m_map = HDTConnector(m_file)
    iter = m_map.search_id("", "", "")
    triple = iter.next()
    s_uri = m_map.id_to_uri( triple.get_subject(), triple_role.subject)
    p_uri = m_map.id_to_uri( triple.get_predicate(), triple_role.predicate)
    o_uri = m_map.id_to_uri( triple.get_object(), triple_role.object)
    s_id = m_map.uri_to_id( s_uri, triple_role.subject)
    p_id = m_map.uri_to_id( p_uri, triple_role.predicate)
    o_id = m_map.uri_to_id( o_uri, triple_role.object)
    self.assertEqual(triple.get_subject(), s_id)
    self.assertEqual(triple.get_predicate(), p_id)
    self.assertEqual(triple.get_object(), o_id)

  def test_should_transform_uri_into_id(self):
    m_map = HDTConnector(m_file)
    iter = m_map.search("", "", "")
    triple = iter.next()
    s_id = m_map.uri_to_id( triple.get_subject(), triple_role.subject)
    p_id = m_map.uri_to_id( triple.get_predicate(), triple_role.predicate)
    o_id = m_map.uri_to_id( triple.get_object(), triple_role.object)
    s_uri = m_map.id_to_uri( s_id, triple_role.subject)
    p_uri = m_map.id_to_uri( p_id, triple_role.predicate)
    o_uri = m_map.id_to_uri( o_id, triple_role.object)
    self.assertEqual(triple.get_subject(), s_uri)
    self.assertEqual(triple.get_predicate(), p_uri)
    self.assertEqual(triple.get_object(), o_uri)

  def test_should_create_c_object_and_delete_when_not_used(self):
    m_map = HDTConnector(m_file)
    del m_map

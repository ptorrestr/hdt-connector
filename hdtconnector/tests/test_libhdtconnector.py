import unittest
import numpy as np
from itertools import islice
from hdtconnector.libhdtconnector import HDTConnector
from hdtconnector.libhdtconnector import triple_role
import subprocess
import os

m_file = "etc/test.hdt"
m_file_literals = "etc/literals.hdt"

class TestHDTConnector(unittest.TestCase):
  def test_should_not_write_to_stdout_when_opening_file(self):
    path = os.path.dirname(os.path.realpath(__file__))
    arg = ["python", path + "/open_hdtconnector_no_notification.py"]
    p = subprocess.run(arg, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    self.assertEqual(len(p.stdout), 0)
    self.assertEqual(len(p.stderr), 0)

  def test_should_write_to_stdout_when_opening_file(self):
    path = os.path.dirname(os.path.realpath(__file__))
    arg = ["python", path + "/open_hdtconnector_notification.py"]
    p = subprocess.run(arg, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
    self.assertGreater(len(p.stdout), 0)
    self.assertEqual(len(p.stderr), 0)

  def test_should_iterate_hdt_file_getting_uris(self):
    m_map = HDTConnector(m_file)
    t_list = list(islice(m_map.search("", "", ""), 10))
    self.assertEqual(len(t_list), 10)

  def test_should_obtain_str_from_a_uri_iterator(self):
    m_map = HDTConnector(m_file)
    triple = next(m_map.search("", "", ""))
    self.assertIsInstance(triple[0], str)
    self.assertIsInstance(triple[1], str)
    self.assertIsInstance(triple[2], str)

  def test_should_iterate_hdt_file_getting_ids(self):
    m_map = HDTConnector(m_file)
    t_list = list(islice(m_map.search_id("", "", ""), 10))
    self.assertEqual(len(t_list), 10)

  def test_should_iterate_hdt_file_by_using_ids_in_search(self):
    m_map = HDTConnector(m_file)
    subject,_,_ = next(m_map.search_id("", "", ""))
    t_list = list(islice(m_map.search_id(subject, 0, 0), 10))
    self.assertEqual(len(t_list), 10)

  def test_should_iterate_search_until_get_a_stop_exception(self):
    m_map = HDTConnector(m_file)
    with self.assertRaises(StopIteration):
      next( m_map.search("some/non/existing/resource", "", ""))

  def test_should_iterate_search_id_with_ids_until_get_a_stop_exception(self):
    m_map = HDTConnector(m_file)
    with self.assertRaises(StopIteration):
      next( m_map.search_id(123123123, 0, 0) )

  def test_should_iterate_search_id_with_uris_until_get_a_stop_exception(self):
    m_map = HDTConnector(m_file)
    with self.assertRaises(StopIteration):
      next( m_map.search_id("some/non/existing/resource", "", ""))

  def test_should_transform_id_into_url(self):
    m_map = HDTConnector(m_file)
    triple = next(m_map.search_id("", "", ""))
    s_uri = m_map.id_to_uri( triple[0], triple_role.subject)
    p_uri = m_map.id_to_uri( triple[1], triple_role.predicate)
    o_uri = m_map.id_to_uri( triple[2], triple_role.object)
    s_id = m_map.uri_to_id( s_uri, triple_role.subject)
    p_id = m_map.uri_to_id( p_uri, triple_role.predicate)
    o_id = m_map.uri_to_id( o_uri, triple_role.object)
    self.assertEqual(triple[0], s_id)
    self.assertEqual(triple[1], p_id)
    self.assertEqual(triple[2], o_id)

  def test_should_transform_uri_into_id(self):
    m_map = HDTConnector(m_file)
    triple = next(m_map.search("", "", ""))
    s_id = m_map.uri_to_id( triple[0], triple_role.subject)
    p_id = m_map.uri_to_id( triple[1], triple_role.predicate)
    o_id = m_map.uri_to_id( triple[2], triple_role.object)
    s_uri = m_map.id_to_uri( s_id, triple_role.subject)
    p_uri = m_map.id_to_uri( p_id, triple_role.predicate)
    o_uri = m_map.id_to_uri( o_id, triple_role.object)
    self.assertEqual(triple[0], s_uri)
    self.assertEqual(triple[1], p_uri)
    self.assertEqual(triple[2], o_uri)

  def test_should_create_c_object_and_delete_when_not_used(self):
    m_map = HDTConnector(m_file)
    del m_map

  def test_should_properly_parse_a_numpy_type(self):
    m_map = HDTConnector(m_file)
    t_list = list(islice(m_map.search_id("", "", ""), 10))
    t_np_array = np.array([ s for s,_,_ in t_list ], dtype = np.uint32)
    for i in range(0, len(t_np_array)):
      m_map.search_id(t_np_array[i], 0, 0)

  def test_should_find_shared_objects(self):
    m_map = HDTConnector(m_file)
    t_list = list(islice(m_map.search_id("", "", ""), 10))
    t_np_array = np.array([ (s, o) for s,_,o in t_list ], dtype = "uint32,uint32")
    for id_sub, id_obj in t_np_array:
        # This dataset does not have shared elements
        print(id_sub, id_obj)
        self.assertFalse(m_map.is_shared(id_sub))
        self.assertFalse(m_map.is_shared(id_obj))

  def test_should_find_literal_objects(self):
    m_map = HDTConnector(m_file_literals)
    t_list = list(islice(m_map.search_id("", "", ""), 10))
    t_np_array = np.array([ (s, o) for s,_,o in t_list ], dtype = "uint32,uint32")
    for id_sub, id_obj in t_np_array:
        # This dataset every object is a literal
        self.assertTrue(m_map.is_literal(id_obj))

  def test_should_find_literal_objects_in_a_four_sec_dictionary(self):
    m_map = HDTConnector(m_file)
    t_list = list(islice(m_map.search_id("", "", ""), 10))
    t_np_array = np.array([ (s, o) for s,_,o in t_list ], dtype = "uint32,uint32")
    for id_sub, id_obj in t_np_array:
      # In this dataset every object is not a literal
      self.assertFalse(m_map.is_literal(id_obj))


  def test_should_iterate_search_id_non_extended(self):
    m_map = HDTConnector(m_file)
    t_list = list(islice(m_map.search_id(0, 0, 0, ext = False), 10))
    for triple in t_list:
      self.assertEqual(len(triple), 3)

  def test_should_iterate_search_id_extended(self):
    m_map = HDTConnector(m_file)
    t_list = list(islice(m_map.search_id(0, 0, 0, ext = True), 10))
    for triple in t_list:
      self.assertEqual(len(triple), 6)

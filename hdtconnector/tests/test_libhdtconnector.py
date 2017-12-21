import unittest
import numpy as np
from itertools import islice
from hdtconnector.libhdtconnector import HDTConnector
from hdtconnector.libhdtconnector import triple_role
import subprocess
import os

m_file = "etc/test.hdt"

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
    self.assertIsInstance(triple.get_subject(), str)
    self.assertIsInstance(triple.get_predicate(), str)
    self.assertIsInstance(triple.get_object(), str)

  def test_should_iterate_hdt_file_getting_ids(self):
    m_map = HDTConnector(m_file)
    t_list = list(islice(m_map.search_id("", "", ""), 10))
    self.assertEqual(len(t_list), 10)

  def test_should_iterate_hdt_file_by_using_ids_in_search(self):
    m_map = HDTConnector(m_file)
    triple = next(m_map.search_id("", "", ""))
    t_list = list(islice(m_map.search_id(triple.get_subject(), 0, 0), 10))
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
    triple = next(m_map.search("", "", ""))
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

  def test_should_properly_parse_a_numpy_type(self):
    m_map = HDTConnector(m_file)
    t_list = list(islice(m_map.search_id("", "", ""), 10))
    t_np_array = np.array([ x.get_subject() for x in t_list ], dtype = np.uint32)
    for i in range(0, len(t_np_array)):
      m_map.search_id(t_np_array[i], 0, 0)


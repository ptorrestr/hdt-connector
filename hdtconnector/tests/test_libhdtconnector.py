import unittest
from hdtconnector.libhdtconnector import HDTConnector

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

  def test_should_create_c_object_and_delete_when_not_used(self):
    m_map = HDTConnector(m_file)
    del m_map

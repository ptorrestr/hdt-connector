import unittest
from hdtconnector.libhdtconnector import HDTConnector

class TestHDTConnector(unittest.TestCase):
  def test_basic_hdt(self):
    m_file = "etc/test.hdt"
    print(type(m_file))
    m_map = HDTConnector(m_file)
    iter = m_map.search("", "", "")
    while iter.has_next():
      print( iter.next() )
